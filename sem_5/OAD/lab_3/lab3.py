import marimo

__generated_with = "0.25.1"
app = marimo.App()


@app.cell
def _():
    import marimo as mo

    return (mo,)


@app.cell(hide_code=True)
def _(mo):
    mo.md(r"""
    # Лабораторная работа №3
    ## Обработка пропущенных значений и выбросов

    Датасет: демонстрационный набор «продажа квартир» (`test_dataset.py`).
    Содержит пропуски типов MCAR / MAR / MNAR и выбросы (ошибки единиц измерения,
    «заглушки», экстремальные значения).
    """)
    return


@app.cell
def _():
    import numpy as np
    import pandas as pd
    import seaborn as sns
    import matplotlib.pyplot as plt
    import scipy.stats as stats

    from sklearn.impute import SimpleImputer, MissingIndicator, KNNImputer
    from sklearn.experimental import enable_iterative_imputer  # noqa
    from sklearn.impute import IterativeImputer
    from sklearn.ensemble import RandomForestRegressor

    sns.set_theme(style="ticks")
    return IterativeImputer, RandomForestRegressor, np, pd, plt, sns, stats


@app.cell(hide_code=True)
def _(mo):
    mo.md(r"""
    ## Загрузка данных
    """)
    return


@app.cell
def _(pd):
    from dataset import _make_demo_dataset

    df_raw = pd.read_csv(filepath_or_buffer='data/house_prices.csv')
    return (df_raw,)


@app.cell
def _(df_raw, np):
    df = df_raw.replace("?", np.nan).copy()
    df.head()
    return (df,)


@app.cell
def _(df):
    [c for c in df.columns]
    return


@app.cell
def _(df):
    df.dtypes
    return


@app.cell
def _(df):
    df.info()
    return


@app.cell
def _(df):
    df.describe().round(3)
    return


@app.cell(hide_code=True)
def _(mo):
    mo.md(r"""
    ## 2.1 Первичный анализ набора данных

    - **Предметная область:** рынок недвижимости (продажа квартир).
    - **Объект:** квартира.
    - **Целевое значение:** `price` — цена квартиры.
    """)
    return


@app.cell
def _(df):
    print("Размер набора данных:", df.shape)
    df.info()
    return


@app.cell
def _(df, pd):
    types_df = pd.DataFrame({
        "Признак": df.columns,
        "Тип dtype": df.dtypes.astype(str).values,
        "Уникальных": [df[c].nunique(dropna=True) for c in df.columns],
        "Пропусков": [int(df[c].isna().sum()) for c in df.columns],
    })
    types_df
    return


@app.cell
def _(df):
    numeric_cols = df.select_dtypes(include="number").columns.tolist()
    cat_cols = df.select_dtypes(include="object").columns.tolist()
    print("Числовые признаки:", numeric_cols)
    print("Категориальные признаки:", cat_cols)
    return cat_cols, numeric_cols


@app.cell
def _(df, numeric_cols):
    df[numeric_cols].describe().T
    return


@app.cell
def _(cat_cols, df):
    for c in cat_cols:
        print(f"=== {c} ===")
        print(df[c].value_counts(dropna=False))
        print()
    return


@app.cell
def _(df, pd):
    # Подозрительные значения, формально не являющиеся пропусками
    suspicious = {
        "age_years < 0": int((df["age_years"] < 0).sum()),
        "age_years > 100": int((df["age_years"] > 100).sum()),
        "area_m2 > 1000": int((df["area_m2"] > 1000).sum()),
        "income_k > 300": int((df["income_k"] > 300).sum()),
        "price > 1e7": int((df["price"] > 1e7).sum()),
    }
    pd.DataFrame(
        suspicious.items(),
        columns=["Проверка", "Количество"]
    ).set_index("Проверка")
    return


@app.cell(hide_code=True)
def _(mo):
    mo.md(r"""
    ## 2.2 Анализ пропущенных значений
    """)
    return


@app.cell
def _(df, pd):
    missing_df = pd.DataFrame({
        "Пропуски": df.isna().sum(),
        "Доля, %": df.isna().mean() * 100,
    })
    missing_df = missing_df[missing_df["Пропуски"] > 0].sort_values("Доля, %", ascending=False)
    missing_df
    return (missing_df,)


@app.cell
def _(missing_df, plt):
    fig_missing, ax_missing = plt.subplots(figsize=(8, 4))
    missing_df["Доля, %"].plot(kind="bar", ax=ax_missing, color="steelblue")
    ax_missing.set_ylabel("Доля пропусков, %")
    ax_missing.set_title("Доля пропусков по признакам")
    plt.tight_layout()
    fig_missing
    return


@app.cell
def _(df, pd):
    # Проверка MAR-гипотезы: доля пропусков income_k по возрастным группам
    df_age = df.copy()
    df_age["age_group"] = pd.cut(
        df_age["age_years"],
        bins=[-1, 25, 35, 50, 100, 1000],
        labels=["<25", "25-35", "35-50", "50-100", ">100"],
    )
    mar_check = (
        df_age.groupby("age_group", observed=False)["income_k"]
        .apply(lambda s: s.isna().mean() * 100)
        .to_frame("Доля пропусков income_k, %")
    )
    mar_check
    return


@app.cell(hide_code=True)
def _(mo):
    mo.md(r"""
    **Вывод по характеру пропусков:**
    - `area_m2`, `distance_km`, `city` — пропуски распределены случайно (MCAR);
    - `income_k` — доля пропусков зависит от возраста (MAR);
    - `condition` — пропуски чаще встречаются для «требует ремонта» (MNAR).
    """)
    return


@app.cell(hide_code=True)
def _(mo):
    mo.md(r"""
    ## 2.3 Выбор способов обработки пропущенных значений

    | Признак | Способ | Обоснование |
    |---|---|---|
    | `area_m2` | медиана + индикатор пропуска | распределение логнормальное, медиана устойчива к выбросам |
    | `distance_km` | медиана + индикатор | распределение скошено вправо |
    | `income_k` | MICE (IterativeImputer + RandomForest) | пропуски MAR, зависят от других признаков |
    | `city` | константа `«Неизвестно»` | сохраняет факт пропуска, не искажает частоты |
    | `condition` | константа `«Неизвестно»` | пропуски MNAR, важно выделить их в отдельную категорию |
    """)
    return


@app.cell(hide_code=True)
def _(mo):
    mo.md(r"""
    ## 2.4 Сравнение способов заполнения пропусков
    """)
    return


@app.cell(hide_code=True)
def _(mo):
    mo.md(r"""
    ### Числовой признак `area_m2`
    """)
    return


@app.cell
def _(df, pd):
    area_orig = df["area_m2"].copy()
    area_mean = area_orig.fillna(area_orig.mean())
    area_median = area_orig.fillna(area_orig.median())

    comp_area = pd.DataFrame({
        "Исходные": area_orig.describe(),
        "Среднее": area_mean.describe(),
        "Медиана": area_median.describe(),
    })
    comp_area
    return area_mean, area_median, area_orig


@app.cell
def _(area_mean, area_median, area_orig, plt, sns):
    fig_area, ax_area = plt.subplots(figsize=(8, 4))
    sns.kdeplot(area_orig.dropna(), ax=ax_area, label="Исходные", color="black")
    sns.kdeplot(area_mean, ax=ax_area, label="Среднее", color="red")
    sns.kdeplot(area_median, ax=ax_area, label="Медиана", color="blue")
    ax_area.set_title("area_m2: KDE до и после заполнения")
    ax_area.legend()
    plt.tight_layout()
    fig_area
    return


@app.cell(hide_code=True)
def _(mo):
    mo.md(r"""
    **Вывод:** заполнение средним заметно смещает распределение вправо из-за
    влияния выбросов. Медиана сохраняет форму распределения лучше.
    """)
    return


@app.cell(hide_code=True)
def _(mo):
    mo.md(r"""
    ### Категориальный признак `city`
    """)
    return


@app.cell
def _(df, pd):
    city_orig = df["city"].copy()
    city_mode = city_orig.fillna(city_orig.mode()[0])
    city_const = city_orig.fillna("Неизвестно")

    freq_comp = pd.DataFrame({
        "Исходные": city_orig.value_counts(dropna=False),
        "Мода": city_mode.value_counts(dropna=False),
        "Константа": city_const.value_counts(dropna=False),
    }).fillna(0).astype(int)
    freq_comp
    return (freq_comp,)


@app.cell
def _(freq_comp, plt):
    fig_city, ax_city = plt.subplots(figsize=(8, 4))
    freq_comp.plot(kind="bar", ax=ax_city)
    ax_city.set_title("city: частоты категорий")
    plt.tight_layout()
    fig_city
    return


@app.cell(hide_code=True)
def _(mo):
    mo.md(r"""
    **Вывод:** заполнение модой увеличивает долю самой частой категории.
    Константа `«Неизвестно»` сохраняет информацию о пропуске и не искажает
    исходные частоты.
    """)
    return


@app.cell(hide_code=True)
def _(mo):
    mo.md(r"""
    ## 2.5 Исследование распределений числовых признаков

    Выберем `area_m2` и `age_years` — в них присутствуют экстремальные значения.
    """)
    return


@app.cell
def _(plt, sns, stats):
    def diagnostic_plots(data, variable, title):
        fig, ax = plt.subplots(2, 2, figsize=(10, 7))
        data[variable].hist(bins=30, ax=ax[0, 0])
        ax[0, 0].set_title("Гистограмма")

        stats.probplot(data[variable].dropna(), dist="norm", plot=ax[0, 1])
        ax[0, 1].set_title("Q-Q plot (normal)")

        sns.violinplot(x=data[variable], ax=ax[1, 0])
        ax[1, 0].set_title("Violin plot")

        sns.boxplot(x=data[variable], ax=ax[1, 1])
        ax[1, 1].set_title("Boxplot")

        fig.suptitle(title)
        plt.tight_layout()
        return fig

    return (diagnostic_plots,)


@app.cell(hide_code=True)
def _(mo):
    mo.md(r"""
    ### Признак `area_m2`
    """)
    return


@app.cell
def _(df, diagnostic_plots):
    diagnostic_plots(df, "area_m2", "area_m2 — исходные данные")
    return


@app.cell
def _(df, stats):
    sample_area = df["area_m2"].dropna().sample(500, random_state=42)
    print(f"Асимметрия: {stats.skew(df['area_m2'].dropna()):.2f}")
    print(f"Эксцесс: {stats.kurtosis(df['area_m2'].dropna()):.2f}")
    print(f"Shapiro-Wilk p-value: {stats.shapiro(sample_area).pvalue:.2e}")
    return


@app.cell
def _(df, np, pd):
    log_area = pd.DataFrame({"log_area": np.log(df["area_m2"].dropna())})
    log_area
    return (log_area,)


@app.cell
def _(diagnostic_plots, log_area):
    diagnostic_plots(log_area, "log_area", "log(area_m2)")
    return


@app.cell(hide_code=True)
def _(mo):
    mo.md(r"""
    **Вывод:** исходное `area_m2` сильно скошено, гипотеза нормальности
    отвергается. После логарифмирования распределение становится близким
    к нормальному — гипотеза логнормального распределения подтверждается.
    """)
    return


@app.cell(hide_code=True)
def _(mo):
    mo.md(r"""
    ### Признак `age_years`
    """)
    return


@app.cell
def _(df, diagnostic_plots):
    diagnostic_plots(df, "age_years", "age_years — исходные данные")
    return


@app.cell
def _(df, stats):
    sample_age = df["age_years"].dropna().sample(500, random_state=42)
    print(f"Асимметрия: {stats.skew(df['age_years'].dropna()):.2f}")
    print(f"Эксцесс: {stats.kurtosis(df['age_years'].dropna()):.2f}")
    print(f"Shapiro-Wilk p-value: {stats.shapiro(sample_age).pvalue:.2e}")
    return


@app.cell(hide_code=True)
def _(mo):
    mo.md(r"""
    **Вывод:** наличие значений `-1` и `999` нарушает нормальность.
    Это «заглушки» и ошибки, которые следует обработать.
    """)
    return


@app.cell(hide_code=True)
def _(mo):
    mo.md(r"""
    ## 2.6 Обнаружение выбросов

    Используем три метода: правило трёх сигм, IQR (K = 1.5) и квантильный (5%/95%).
    Для корректного поиска выбросов сначала заполним пропуски.
    """)
    return


@app.cell
def _(IterativeImputer, RandomForestRegressor, df):
    df_imputed = df.copy()

    # Числовые пропуски: медиана
    for col in ["area_m2", "distance_km"]:
        df_imputed[col] = df_imputed[col].fillna(df_imputed[col].median())

    # income_k через MICE
    mice_cols = [
        "area_m2", "rooms", "age_years", "distance_km",
        "income_k", "parking", "price",
    ]
    mice_imputer = IterativeImputer(
        estimator=RandomForestRegressor(n_estimators=10, random_state=0),
        max_iter=10,
        random_state=0,
    )
    mice_result = mice_imputer.fit_transform(df_imputed[mice_cols])
    df_imputed["income_k"] = mice_result[:, mice_cols.index("income_k")]

    # Категориальные — константа
    for col in ["city", "condition"]:
        df_imputed[col] = df_imputed[col].fillna("Неизвестно")

    print("Пропусков после заполнения:", int(df_imputed.isna().sum().sum()))
    return (df_imputed,)


@app.function
def get_boundaries(series, method, K=1.5):
    if method == "3sigma":
        lower = series.mean() - 3 * series.std()
        upper = series.mean() + 3 * series.std()
    elif method == "IQR":
        Q1 = series.quantile(0.25)
        Q3 = series.quantile(0.75)
        IQR = Q3 - Q1
        lower = Q1 - K * IQR
        upper = Q3 + K * IQR
    elif method == "quantile":
        lower = series.quantile(0.05)
        upper = series.quantile(0.95)
    else:
        raise ValueError("Unknown method")
    return lower, upper


@app.cell
def _(df_imputed, pd):
    def _():
        outlier_rows = []
        for col in ["area_m2", "age_years"]:
            for method in ["3sigma", "IQR", "quantile"]:
                lower, upper = get_boundaries(df_imputed[col], method)
                mask = (df_imputed[col] < lower) | (df_imputed[col] > upper)
                outlier_rows.append({
                    "Признак": col,
                    "Метод": method,
                    "Нижняя граница": round(lower, 2),
                    "Верхняя граница": round(upper, 2),
                    "Кол-во выбросов": int(mask.sum()),
                    "Доля, %": round(mask.mean() * 100, 2),
                })

        outlier_df = pd.DataFrame(outlier_rows)
        return outlier_df


    _()
    return


@app.cell(hide_code=True)
def _(mo):
    mo.md(r"""
    **Сравнение методов:**
    - `area_m2` — асимметричное распределение, 3σ даёт широкие границы и
      находит мало выбросов. IQR устойчивее.
    - Квантильный подход всегда выделяет около 10% наблюдений, он не различает
      истинные выбросы и «хвосты» распределения.
    - `age_years` — IQR и 3σ ловят `999`, но не ловят `-1`. Значение `-1` —
      явная ошибка и обрабатывается отдельно.
    """)
    return


@app.cell(hide_code=True)
def _(mo):
    mo.md(r"""
    ## 2.7 Обработка выбросов

    - `area_m2` — винзоризация по границам IQR (K = 1.5);
    - `age_years` — значения < 0 или > 100 заменяем на медиану;
    - `income_k` — винзоризация по границам IQR (K = 1.5);
    - `price` — винзоризация по границам IQR (K = 3).
    """)
    return


@app.cell
def _(df_imputed):
    df_processed = df_imputed.copy()
    return (df_processed,)


@app.cell
def _(df_processed, np):
    lower_a, upper_a = get_boundaries(df_processed["area_m2"], "IQR")
    df_processed["area_m2"] = np.clip(df_processed["area_m2"], lower_a, upper_a)

    print(f"area_m2: границы [{lower_a:.2f}, {upper_a:.2f}]")
    return


@app.cell
def _(df_processed, np):
    mask_age = (df_processed["age_years"] < 0) | (df_processed["age_years"] > 100)
    print("Некорректных age_years:", int(mask_age.sum()))
    df_processed.loc[mask_age, "age_years"] = np.nan
    df_processed["age_years"] = df_processed["age_years"].fillna(
        df_processed["age_years"].median()
    )
    return


@app.cell
def _(df_processed, np):
    lower_i, upper_i = get_boundaries(df_processed["income_k"], "IQR")
    df_processed["income_k"] = np.clip(df_processed["income_k"], lower_i, upper_i)

    lower_p, upper_p = get_boundaries(df_processed["price"], "IQR", K=3)
    df_processed["price"] = np.clip(df_processed["price"], lower_p, upper_p)

    print(f"income_k: границы [{lower_i:.2f}, {upper_i:.2f}]")
    print(f"price: границы [{lower_p:.2f}, {upper_p:.2f}]")
    return


@app.cell
def _(df_processed, diagnostic_plots):
    diagnostic_plots(df_processed, "area_m2", "area_m2 — после обработки")
    return


@app.cell
def _(df_processed, diagnostic_plots):
    diagnostic_plots(df_processed, "age_years", "age_years — после обработки")
    return


@app.cell
def _(df_processed, diagnostic_plots):
    diagnostic_plots(df_processed, "income_k", "income_k — после обработки")
    return


@app.cell
def _(df_processed, diagnostic_plots):
    diagnostic_plots(df_processed, "price", "price — после обработки")
    return


@app.cell(hide_code=True)
def _(mo):
    mo.md(r"""
    **Вывод:** экстремальные ошибки устранены, распределения стали компактнее.
    Медианы изменились незначительно — основная структура данных сохранена.
    """)
    return


@app.cell(hide_code=True)
def _(mo):
    mo.md(r"""
    ## 2.8 Сравнение исходного и обработанного наборов данных
    """)
    return


@app.cell
def _(df, df_processed, pd):
    def _():
        summary_rows = []
        for col in ["area_m2", "age_years", "income_k", "price"]:
            summary_rows.append({
                "Признак": col,
                "mean до": round(df[col].mean(), 2),
                "mean после": round(df_processed[col].mean(), 2),
                "median до": round(df[col].median(), 2),
                "median после": round(df_processed[col].median(), 2),
                "std до": round(df[col].std(), 2),
                "std после": round(df_processed[col].std(), 2),
                "min до": round(df[col].min(), 2),
                "min после": round(df_processed[col].min(), 2),
                "max до": round(df[col].max(), 2),
                "max после": round(df_processed[col].max(), 2),
            })

        summary_df = pd.DataFrame(summary_rows).set_index("Признак")
        return summary_df


    _()
    return


@app.cell
def _(df, df_processed):
    print(f"Размер до:      {df.shape}")
    print(f"Размер после:   {df_processed.shape}")
    print(f"Пропусков до:   {int(df.isna().sum().sum())}")
    print(f"Пропусков после:{int(df_processed.isna().sum().sum())}")
    return


@app.cell(hide_code=True)
def _(mo):
    mo.md(r"""
    Сохраним полученный датасет для 4 лабораторной работы
    """)
    return


@app.cell
def _(df_processed):
    df_processed.to_csv(path_or_buf='data/house_prices_processed.csv', index=False)
    return


@app.cell(hide_code=True)
def _(mo):
    mo.md(r"""
    **Итоговый вывод:** выполнена обработка пропущенных значений и выбросов.
    Для числовых признаков применены медиана, MICE и винзоризация; для
    категориальных — константа `«Неизвестно»`. Итоговый набор не содержит
    пропусков, экстремальные ошибки заменены на границы или медианы. Обработка
    не привела к существенному смещению медиан, но уменьшила разброс и
    устранила аномалии, которые могли бы негативно повлиять на модели
    машинного обучения.
    """)
    return


if __name__ == "__main__":
    app.run()
