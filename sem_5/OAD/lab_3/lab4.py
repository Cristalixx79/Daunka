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
    # Лабораторная работа №4
    ## Разведочный анализ данных (EDA)

    Используем датасет, полученный по результатам лабораторной работы №3
    (`data/house_prices_processed.csv`): данные о продаже квартир после
    обработки пропусков и выбросов.

    **Предметная область:** рынок недвижимости.
    **Объект:** квартира.
    **Целевой признак:** `price` — цена квартиры.
    """)
    return


@app.cell
def _():
    import numpy as np
    import pandas as pd
    import seaborn as sns
    import matplotlib.pyplot as plt
    import scipy.stats as stats
    from sklearn.preprocessing import (
        LabelEncoder,
        OneHotEncoder,
        StandardScaler,
        MinMaxScaler,
        RobustScaler,
    )

    sns.set_theme(style="ticks")
    return (
        LabelEncoder,
        MinMaxScaler,
        RobustScaler,
        StandardScaler,
        np,
        pd,
        plt,
        sns,
    )


@app.cell(hide_code=True)
def _(mo):
    mo.md(r"""
    ## Загрузка датасета
    """)
    return


@app.cell
def _(pd):
    df = pd.read_csv("data/house_prices_processed.csv")
    return (df,)


@app.cell
def _(df):
    print("Размер набора данных:", df.shape)
    df.head()
    return


@app.cell
def _(df):
    df.dtypes
    return


@app.cell(hide_code=True)
def _(mo):
    mo.md(r"""
    ## 2.1 Первичный анализ признакового пространства
    """)
    return


@app.cell
def _(df, pd):
    types_df = pd.DataFrame({
        "Признак": df.columns,
        "dtype": df.dtypes.astype(str).values,
        "Уникальных": [df[c].nunique() for c in df.columns],
        "Роль": [
            "идентификатор",
            "числовой (непрерывный)",
            "числовой (дискретный)",
            "числовой (непрерывный)",
            "числовой (непрерывный)",
            "числовой (непрерывный)",
            "категориальный (номинальный)",
            "категориальный (порядковый)",
            "числовой (дискретный)",
            "целевой (непрерывный)",
        ],
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
    # Описательные характеристики числовых признаков
    df[numeric_cols].describe().T
    return


@app.cell
def _(cat_cols, df):
    # Частотные характеристики категориальных признаков
    for c in cat_cols:
        print(f"=== {c} ===")
        print(df[c].value_counts(dropna=False))
        print()
    return


@app.cell(hide_code=True)
def _(mo):
    mo.md(r"""
    **Вывод 2.1.** В наборе 1 идентификатор (`id`), 6 числовых признаков,
    2 категориальных (`city` — номинальный, `condition` — порядковый),
    1 бинарный (`parking`) и целевой `price`. Пропусков нет —
    набор подготовлен на предыдущей лабораторной работе.
    """)
    return


@app.cell(hide_code=True)
def _(mo):
    mo.md(r"""
    ## 2.2 Кодирование категориальных признаков

    Для каждого категориального признака выбираем способ кодирования:
    | Признак | Тип | Способ | Обоснование |
    |---|---|---|---|
    | `city` | номинальный | One-Hot | нет естественного порядка, категорий мало |
    | `condition` | порядковый | Ordinal (ручной mapping) | есть естественный порядок: требует ремонта < хорошее < отличное |
    | `parking` | бинарный | без изменений | уже 0/1 |
    """)
    return


@app.cell
def _(df):
    df_enc = df.copy()
    # id не является признаком — удаляем
    df_enc = df_enc.drop(columns=["id"])
    df_enc.head()
    return (df_enc,)


@app.cell
def _(LabelEncoder, df_enc):
    # Демонстрация LabelEncoder на признаке city
    le_city = LabelEncoder()
    city_le = le_city.fit_transform(df_enc["city"])
    print("Уникальные city:", df_enc["city"].unique())
    print("LabelEncoder ->", sorted(set(city_le)))
    print("inverse_transform(0..n) ->", le_city.inverse_transform(range(len(le_city.classes_))))
    return


@app.cell
def _(df_enc):
    # Порядковое кодирование condition: ручной mapping сохраняет смысл порядка
    cond_order = {
        "Неизвестно": -1,
        "требует ремонта": 0,
        "хорошее": 1,
        "отличное": 2,
    }
    df_enc["condition_ord"] = df_enc["condition"].map(cond_order)
    df_enc[["condition", "condition_ord"]].drop_duplicates().sort_values("condition_ord")
    return


@app.cell
def _(df_enc, pd):
    # One-Hot кодирование city
    city_dummies = pd.get_dummies(df_enc["city"], prefix="city", drop_first=True).astype(int)
    df_enc2 = pd.concat([df_enc, city_dummies], axis=1)
    df_enc2.head()
    return (df_enc2,)


@app.cell
def _(df_enc2):
    # Удаляем исходные текстовые колонки
    df_enc3 = df_enc2.drop(columns=["city", "condition"])
    print("Итоговые колонки:")
    print(df_enc3.columns.tolist())
    df_enc3.head()
    return (df_enc3,)


@app.cell(hide_code=True)
def _(mo):
    mo.md(r"""
    **Вывод 2.2.** `city` закодирован One-Hot (порядок отсутствует),
    `condition` — порядковым кодом (естественный порядок состояния квартиры),
    `parking` уже бинарный. Итоговый набор готов к анализу.
    """)
    return


@app.cell(hide_code=True)
def _(mo):
    mo.md(r"""
    ## 2.3 Предметно обусловленное конструирование признаков

    Исходя из смысла исходных признаков, создадим:

    1. `area_per_room = area_m2 / rooms` — средняя площадь на одну комнату
       (позволяет оценить «просторность» квартиры);
    2. `income_distance = income_k / (distance_km + 1)` — «доступность района»:
       сколько дохода района приходится на единицу удалённости от центра;
    3. `is_old = 1, если age_years > 40` — флаг «старый дом».
    """)
    return


@app.cell
def _(df_enc3):
    df_feat = df_enc3.copy()
    df_feat["area_per_room"] = df_feat["area_m2"] / df_feat["rooms"]
    df_feat["income_distance"] = df_feat["income_k"] / (df_feat["distance_km"] + 1)
    df_feat["is_old"] = (df_feat["age_years"] > 40).astype(int)
    df_feat.head()
    return (df_feat,)


@app.cell
def _(df_feat):
    df_feat[["area_per_room", "income_distance", "is_old"]].describe().T
    return


@app.cell(hide_code=True)
def _(mo):
    mo.md(r"""
    **Вывод 2.3.** Создано три предметно-обоснованных признака.
    `area_per_room` и `income_distance` — числовые, `is_old` — бинарный.
    Все они могут нести дополнительную информацию о цене квартиры.
    """)
    return


@app.cell(hide_code=True)
def _(mo):
    mo.md(r"""
    ## 2.4 Линеаризация зависимости

    Для каждого непрерывного признака строим диаграмму рассеяния
    зависимости `price` от признака. Выбираем признаки с выраженной
    нелинейной зависимостью и предлагаем преобразование.
    """)
    return


@app.cell
def _(df_feat, plt, sns):
    cont_features = [
        "area_m2",
        "age_years",
        "distance_km",
        "income_k",
        "area_per_room",
        "income_distance",
    ]
    fig, axes = plt.subplots(2, 3, figsize=(16, 8))
    for ax, col in zip(axes.ravel(), cont_features):
        sns.scatterplot(data=df_feat, x=col, y="price", ax=ax, alpha=0.4)
        ax.set_title(f"price vs {col}")
    plt.tight_layout()
    fig
    return (axes,)


@app.cell(hide_code=True)
def _(mo):
    mo.md(r"""
    По графикам:
    - `price` и `area_m2` — выраженная положительная, но с разбросом зависимость;
    - `price` и `distance_km` — выраженная нелинейная (убывающая) зависимость;
    - `price` и `income_k` — слабая связь.

    Выберем `area_m2` и `distance_km` как наиболее показательные и применим
    логарифмирование `price` (мультипликативная природа цены).
    """)
    return


@app.cell
def _(df_feat, np):
    df_lin = df_feat.copy()
    df_lin["log_price"] = np.log(df_lin["price"])
    df_lin["log_area_m2"] = np.log(df_lin["area_m2"] + 1)
    return (df_lin,)


@app.cell
def _(df_lin):
    df_lin.head()
    return


@app.cell
def _(axes, df_lin, plt, sns):
    fig2, axes2 = plt.subplots(2, 2, figsize=(14, 10))
    sns.scatterplot(data=df_lin, x="area_m2", y="price", ax=axes2[0, 0], alpha=0.4)
    axes[0, 0].set_title("area_m2 vs price (исходное)")

    sns.scatterplot(data=df_lin, x="area_m2", y="log_price", ax=axes2[0, 1], alpha=0.4)
    axes2[0, 1].set_title("area_m2 vs log(price)")

    sns.scatterplot(data=df_lin, x="distance_km", y="price", ax=axes2[1, 0], alpha=0.4)
    axes2[1, 0].set_title("distance_km vs price (исходное)")

    sns.scatterplot(data=df_lin, x="distance_km", y="log_price", ax=axes2[1, 1], alpha=0.4)
    axes2[1, 1].set_title("distance_km vs log(price)")

    plt.tight_layout()
    fig2
    return


@app.cell(hide_code=True)
def _(mo):
    mo.md(r"""
    **Вывод 2.4.** После перехода к `log(price)`:
    - зависимость цены от `area_m2` стала заметно ближе к линейной;
    - связь `distance_km` и `log(price)` также линеаризовалась.
    Новый признак `log_price` полезен для дальнейшего анализа.
    """)
    return


@app.cell(hide_code=True)
def _(mo):
    mo.md(r"""
    ## 2.5 Корреляционный анализ

    Рассчитаем матрицы корреляции Пирсона и Спирмена для итогового
    набора признаков.
    """)
    return


@app.cell
def _(df_lin):
    # Убираем log_price из общего списка для матриц (это производная от price),
    # чтобы не дублировать целевую переменную
    corr_features = [c for c in df_lin.columns if c not in ["log_price"]]
    print("Признаки для корреляционного анализа:")
    print(corr_features)
    return (corr_features,)


@app.cell
def _(corr_features, df_lin):
    pearson_corr = df_lin[corr_features].corr(method="pearson")
    pearson_corr
    return (pearson_corr,)


@app.cell
def _(corr_features, df_lin):
    spearman_corr = df_lin[corr_features].corr(method="spearman")
    spearman_corr
    return (spearman_corr,)


@app.cell
def _(pearson_corr, plt, sns):
    fig_p, ax_p = plt.subplots(figsize=(11, 9))
    sns.heatmap(pearson_corr, annot=True, fmt=".2f", cmap="coolwarm",
                center=0, ax=ax_p, cbar_kws={"shrink": 0.8})
    ax_p.set_title("Матрица корреляции Пирсона")
    plt.tight_layout()
    fig_p
    return


@app.cell
def _(plt, sns, spearman_corr):
    fig_s, ax_s = plt.subplots(figsize=(11, 9))
    sns.heatmap(spearman_corr, annot=True, fmt=".2f", cmap="coolwarm",
                center=0, ax=ax_s, cbar_kws={"shrink": 0.8})
    ax_s.set_title("Матрица корреляции Спирмена")
    plt.tight_layout()
    fig_s
    return


@app.cell(hide_code=True)
def _(mo):
    mo.md(r"""
    ## 2.6 Сравнение коэффициентов корреляции

    Найдём пары признаков, где коэффициенты Пирсона и Спирмена
    заметно различаются — это признак нелинейной (но монотонной) связи.
    """)
    return


@app.cell
def _(pd, pearson_corr, spearman_corr):
    # Матрица абсолютных разностей (по модулю)
    diff_matrix = (pearson_corr - spearman_corr).abs()

    # Верхний треугольник без диагонали
    diff_pairs = []
    cols = list(pearson_corr.columns)
    for i in range(len(cols)):
        for j in range(i + 1, len(cols)):
            diff_pairs.append({
                "Пара": f"{cols[i]} — {cols[j]}",
                "Пирсон": round(pearson_corr.iloc[i, j], 3),
                "Спирмен": round(spearman_corr.iloc[i, j], 3),
                "|Δ|": round(diff_matrix.iloc[i, j], 3),
            })

    diff_df = pd.DataFrame(diff_pairs).sort_values("|Δ|", ascending=False).reset_index(drop=True)
    diff_df.head(10)
    return


@app.cell(hide_code=True)
def _(mo):
    mo.md(r"""
    **Вывод 2.6.** Наибольшие расхождения между Пирсоном и Спирменом
    наблюдаются для пар с нелинейной монотонной зависимостью —
    например, `distance_km` с ценой и `age_years` с ценой.
    Это подтверждает необходимость линеаризации (см. п. 2.4).

    Связь с целевым признаком `price`:
    - `area_m2`, `area_per_room` — сильная положительная связь;
    - `income_k`, `income_distance` — слабая или умеренная;
    - `distance_km`, `age_years` — умеренная отрицательная.

    Предположения из п. 2.3 подтвердились: `area_per_room` действительно
    коррелирует с ценой, но не сильнее, чем исходная `area_m2`.
    """)
    return


@app.cell(hide_code=True)
def _(mo):
    mo.md(r"""
    ## 2.7 Масштабирование признаков

    Сравним признаки `area_m2` (порядок ~10¹) и `price` (порядок ~10⁴),
    существенно различающиеся по масштабу. Применим к ним три метода:
    Z-оценка (`StandardScaler`), MinMax (`MinMaxScaler`) и масштабирование
    по медиане (`RobustScaler`).
    """)
    return


@app.cell
def _(df_lin):
    scale_features = ["area_m2", "price"]
    df_lin[scale_features].describe().T
    return (scale_features,)


@app.cell
def _(df_lin, scale_features):
    print("До масштабирования:")
    print(df_lin[scale_features].agg(["min", "max", "mean", "std"]).T)
    return


@app.cell
def _(StandardScaler, df_lin, pd):
    std_scaler = StandardScaler()
    area_std = std_scaler.fit_transform(df_lin[["area_m2"]])
    price_std = std_scaler.fit_transform(df_lin[["price"]])

    df_std = pd.DataFrame({
        "area_m2_std": area_std.ravel(),
        "price_std": price_std.ravel(),
    })
    df_std.describe().T
    return (df_std,)


@app.cell
def _(MinMaxScaler, df_lin, pd):
    mm_scaler = MinMaxScaler()
    area_mm = mm_scaler.fit_transform(df_lin[["area_m2"]])
    price_mm = mm_scaler.fit_transform(df_lin[["price"]])

    df_mm = pd.DataFrame({
        "area_m2_mm": area_mm.ravel(),
        "price_mm": price_mm.ravel(),
    })
    df_mm.describe().T
    return (df_mm,)


@app.cell
def _(RobustScaler, df_lin, pd):
    rb_scaler = RobustScaler()
    area_rb = rb_scaler.fit_transform(df_lin[["area_m2"]])
    price_rb = rb_scaler.fit_transform(df_lin[["price"]])

    df_rb = pd.DataFrame({
        "area_m2_rb": area_rb.ravel(),
        "price_rb": price_rb.ravel(),
    })
    df_rb.describe().T
    return (df_rb,)


@app.cell
def _(df_lin, df_mm, df_rb, df_std, plt, sns):
    fig3, axes3 = plt.subplots(2, 3, figsize=(16, 8))

    # area_m2
    sns.kdeplot(df_lin["area_m2"], ax=axes3[0, 0], color="black")
    axes3[0, 0].set_title("area_m2 — исходное")

    sns.kdeplot(df_std["area_m2_std"], ax=axes3[0, 1], color="red")
    axes3[0, 1].set_title("area_m2 — StandardScaler")

    sns.kdeplot(df_mm["area_m2_mm"], ax=axes3[0, 2], color="green")
    axes3[0, 2].set_title("area_m2 — MinMaxScaler")

    # price
    sns.kdeplot(df_lin["price"], ax=axes3[1, 0], color="black")
    axes3[1, 0].set_title("price — исходное")

    sns.kdeplot(df_std["price_std"], ax=axes3[1, 1], color="red")
    axes3[1, 1].set_title("price — StandardScaler")

    sns.kdeplot(df_rb["price_rb"], ax=axes3[1, 2], color="blue")
    axes3[1, 2].set_title("price — RobustScaler")

    plt.tight_layout()
    fig3
    return


@app.cell(hide_code=True)
def _(mo):
    mo.md(r"""
    ### 2.7.1 Сравнение способов масштабирования
    """)
    return


@app.cell
def _(pd):
    # Сводная таблица: min / max / mean / std для каждого варианта
    summary = pd.DataFrame({
        "area_m2 исходное": ["min/max/mean/std", "5.4/987.6/55.4/60.2"],
        "price исходное": ["min/max/mean/std", "3.1e3/9.9e4/1.3e4/6.3e3"],
    })
    # Для наглядности соберём реальные числа программно:
    summary = None
    return


@app.cell
def _(df_lin, df_mm, df_rb, df_std, pd):
    def stats_row(name, series):
        return {
            "Вариант": name,
            "min": round(float(series.min()), 3),
            "max": round(float(series.max()), 3),
            "mean": round(float(series.mean()), 3),
            "std": round(float(series.std()), 3),
        }

    rows = []
    rows.append(stats_row("area_m2 исходное", df_lin["area_m2"]))
    rows.append(stats_row("area_m2 StandardScaler", df_std["area_m2_std"]))
    rows.append(stats_row("area_m2 MinMaxScaler", df_mm["area_m2_mm"]))
    rows.append(stats_row("area_m2 RobustScaler", df_rb["area_m2_rb"]))
    rows.append(stats_row("price исходное", df_lin["price"]))
    rows.append(stats_row("price StandardScaler", df_std["price_std"]))
    rows.append(stats_row("price MinMaxScaler", df_mm["price_mm"]))
    rows.append(stats_row("price RobustScaler", df_rb["price_rb"]))

    scale_summary = pd.DataFrame(rows).set_index("Вариант")
    scale_summary
    return


@app.cell(hide_code=True)
def _(mo):
    mo.md(r"""
    **Сравнение по признакам:**

    - `area_m2`:
      - `StandardScaler` приводит mean к 0, std к 1, форму распределения сохраняет;
      - `MinMaxScaler` приводит к диапазону [0, 1], форма распределения искажается;
      - `RobustScaler` центрирует по медиане и делит на IQR — устойчив к выбросам.
    - `price`:
      - распределение сильно скошено; `StandardScaler` сохраняет асимметрию,
        но делает её более выраженной в масштабе std;
      - `MinMaxScaler` сжимает всё в [0, 1], но 99% значений окажется в узком
        диапазоне из-за одного выброса;
      - `RobustScaler` даёт более равномерное распределение.
    """)
    return


@app.cell(hide_code=True)
def _(mo):
    mo.md(r"""
    ## Итоговый выбор способа масштабирования

    Для итогового набора данных выбираем **`RobustScaler`** для признаков
    с выбросами (`area_m2`, `price`, `income_k`, `distance_km`) и
    **`StandardScaler`** для остальных числовых признаков.

    Обоснование: в данных есть естественные выбросы (большие квартиры,
    дорогие объекты), которые могут сильно смещать среднее и std.
    `RobustScaler` использует медиану и IQR, поэтому устойчив к ним.
    """)
    return


@app.cell
def _(RobustScaler, StandardScaler, df_feat):
    df_scaled = df_feat.copy()

    robust_cols = ["area_m2", "price", "income_k", "distance_km"]
    standard_cols = ["rooms", "age_years", "area_per_room", "income_distance"]

    rb = RobustScaler()
    st = StandardScaler()

    df_scaled[robust_cols] = rb.fit_transform(df_scaled[robust_cols])
    df_scaled[standard_cols] = st.fit_transform(df_scaled[standard_cols])

    df_scaled.head()
    return (df_scaled,)


@app.cell
def _(df_scaled):
    df_scaled.describe().T
    return


@app.cell
def _(df_scaled):
    # Сохраним итоговый набор (в масштабированном виде)
    df_scaled.to_csv("data/house_prices_eda.csv", index=False)
    print("Сохранено в data/house_prices_eda.csv")
    return


@app.cell(hide_code=True)
def _(mo):
    mo.md(r"""
    ## Итоговые выводы

    1. **Первичный анализ.** В наборе 1 идентификатор, 6 числовых,
       2 категориальных, 1 бинарный и 1 целевой признак. Пропусков нет.
    2. **Кодирование.** `city` — One-Hot, `condition` — порядковый код,
       `parking` — без изменений.
    3. **Конструирование признаков.** Созданы `area_per_room`,
       `income_distance`, `is_old`.
    4. **Линеаризация.** Логарифмирование `price` линеаризовало
       зависимости от `area_m2` и `distance_km`.
    5. **Корреляционный анализ.** Пирсон и Спирмен дают согласованные
       оценки для линейных пар и расходятся для монотонных нелинейных
       (например, `distance_km` — `price`).
    6. **Масштабирование.** Для устойчивости к выбросам выбран
       `RobustScaler` для «тяжёлых» признаков и `StandardScaler`
       для остальных.
    """)
    return


if __name__ == "__main__":
    app.run()
