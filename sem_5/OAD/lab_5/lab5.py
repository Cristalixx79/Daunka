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
    # Лабораторная работа №5
    ## Реализация линейной регрессии и градиентной оптимизации

    Датасет из ЛР №3–4 (продажа квартир). Та же предобработка, что в ЛР №3–4.

    Сравниваем две версии:
    - **unscaled** — без масштабирования;
    - **scaled** — с `RobustScaler` для непрерывных признаков.
    """)
    return


@app.cell
def _():
    import numpy as np
    import pandas as pd
    import matplotlib.pyplot as plt
    import seaborn as sns
    from abc import ABC, abstractmethod
    from sklearn.linear_model import LinearRegression, SGDRegressor, HuberRegressor
    from sklearn.preprocessing import RobustScaler
    from sklearn.model_selection import train_test_split
    from sklearn.impute import SimpleImputer
    from sklearn.metrics import mean_squared_error

    sns.set_theme(style="ticks")
    np.random.seed(42)
    return (
        ABC,
        HuberRegressor,
        LinearRegression,
        RobustScaler,
        SimpleImputer,
        abstractmethod,
        mean_squared_error,
        np,
        pd,
        plt,
        train_test_split,
    )


@app.cell(hide_code=True)
def _(mo):
    mo.md(r"""
    ## 2.1 Подготовка набора данных
    """)
    return


@app.cell
def _(pd):
    df_raw = pd.read_csv('data/house_prices.csv')
    df_raw.head()
    return (df_raw,)


@app.cell
def _(SimpleImputer, df_raw):
    df_clean = df_raw.copy()
    cont_imp = ["area_m2", "distance_km", "income_k", "age_years"]
    df_clean[cont_imp] = SimpleImputer(strategy="median").fit_transform(
        df_clean[cont_imp]
    )
    for cat_col in ["city", "condition"]:
        df_clean[cat_col] = df_clean[cat_col].fillna("Неизвестно")

    print(f"Пропусков после заполнения: {df_clean.isna().sum().sum()}")
    return (df_clean,)


@app.cell
def _(df_clean, np):
    df_out = df_clean.copy()

    def clip_iqr(df, col, k=1.5):
        q1 = df[col].quantile(0.25)
        q3 = df[col].quantile(0.75)
        iqr = q3 - q1
        return np.clip(df[col], q1 - k * iqr, q3 + k * iqr)

    df_out.loc[
        (df_out["age_years"] < 0) | (df_out["age_years"] > 100),
        "age_years",
    ] = np.nan
    df_out["age_years"] = df_out["age_years"].fillna(
        df_out["age_years"].median()
    )

    for cont_col in ["area_m2", "income_k", "distance_km"]:
        df_out[cont_col] = clip_iqr(df_out, cont_col)
    df_out["price"] = clip_iqr(df_out, "price", k=3)

    df_out[
        ["area_m2", "age_years", "distance_km", "income_k", "price"]
    ].describe().T
    return (df_out,)


@app.cell
def _(df_out, np, pd):
    df_feat = df_out.copy()
    df_feat["area_per_room"] = df_feat["area_m2"] / df_feat["rooms"]
    df_feat["income_distance"] = (
        df_feat["income_k"] / (df_feat["distance_km"] + 1)
    )
    df_feat["is_old"] = (df_feat["age_years"] > 40).astype(int)
    df_feat["log_price"] = np.log(df_feat["price"])

    cond_map = {"Неизвестно": -1, "требует ремонта": 0,
                "хорошее": 1, "отличное": 2}
    df_feat["condition_ord"] = df_feat["condition"].map(cond_map)

    city_d = pd.get_dummies(
        df_feat["city"], prefix="city", drop_first=True
    ).astype(int)
    df_feat = pd.concat([df_feat, city_d], axis=1)
    df_feat = df_feat.drop(columns=["id", "city", "condition", "price"])

    print(f"Итоговый набор: {df_feat.shape}")
    df_feat.head()
    return (df_feat,)


@app.cell
def _(df_feat):
    target_col = "log_price"
    feature_cols = [c for c in df_feat.columns if c != target_col]
    X = df_feat[feature_cols].values
    y = df_feat[target_col].values
    print(f"X: {X.shape}, y: {y.shape}")
    print(f"Признаки: {feature_cols}")
    return X, feature_cols, y


@app.cell
def _(RobustScaler, X, feature_cols):
    X_unscaled = X.copy()

    continuous = ["area_m2", "age_years", "distance_km", "income_k",
                  "area_per_room", "income_distance"]
    cont_idx = [feature_cols.index(c) for c in continuous]

    X_scaled = X.copy()
    X_scaled[:, cont_idx] = RobustScaler().fit_transform(
        X[:, cont_idx]
    )

    print("Масштабированы:", continuous)
    print("Не масштабированы:",
          [c for c in feature_cols if c not in continuous])
    return X_scaled, X_unscaled


@app.cell
def _(X_scaled, X_unscaled, np, train_test_split, y):
    idx = np.arange(len(y))
    idx_trainval, idx_test = train_test_split(
        idx, test_size=0.2, random_state=42
    )
    idx_train, idx_val = train_test_split(
        idx_trainval, test_size=0.25, random_state=42
    )

    X_un_tr = X_unscaled[idx_train]
    X_un_va = X_unscaled[idx_val]
    X_un_te = X_unscaled[idx_test]

    X_sc_tr = X_scaled[idx_train]
    X_sc_va = X_scaled[idx_val]
    X_sc_te = X_scaled[idx_test]

    y_tr = y[idx_train]
    y_va = y[idx_val]
    y_te = y[idx_test]

    print(f"Train: {len(y_tr)}, Val: {len(y_va)}, Test: {len(y_te)}")
    return (
        X_sc_te,
        X_sc_tr,
        X_sc_va,
        X_un_te,
        X_un_tr,
        X_un_va,
        y_te,
        y_tr,
        y_va,
    )


@app.cell(hide_code=True)
def _(mo):
    mo.md(r"""
    ## 2.2 Архитектура программной реализации
    """)
    return


@app.cell
def _(ABC, abstractmethod):
    class LossBase(ABC):
        @abstractmethod
        def value(self, w, X, y): ...
        @abstractmethod
        def grad(self, w, X, y): ...
        @abstractmethod
        def hessian(self, w, X, y): ...

    return (LossBase,)


@app.cell
def _(ABC, abstractmethod):
    class OptimizerBase(ABC):
        @abstractmethod
        def step(self, w, grad): ...
        def uses_batches(self):
            return False

    return (OptimizerBase,)


@app.cell(hide_code=True)
def _(mo):
    mo.md(r"""
    ## 2.3 Реализация линейной регрессионной модели
    """)
    return


@app.cell
def _(np):
    class LinearRegressionModel:
        def __init__(self, loss, optimizer, fit_intercept=True):
            self.loss = loss
            self.optimizer = optimizer
            self.fit_intercept = fit_intercept
            self.w = None
            self.history = {"loss": [], "grad_norm": [],
                            "cond": [], "val_loss": []}
            self.n_iter_ = 0
            self.converged_ = False

        def _augment(self, X):
            if self.fit_intercept:
                return np.hstack([np.ones((X.shape[0], 1)), X])
            return X

        def fit(self, X, y, eps=1e-6, max_iter=10000,
                X_val=None, y_val=None, cond_every=10):
            Xa = self._augment(X)
            self.w = np.zeros(Xa.shape[1])
            self.history = {"loss": [], "grad_norm": [],
                            "cond": [], "val_loss": []}
            self.converged_ = False
            k_mdl = 0

            for k_mdl in range(max_iter):
                full_grad = self.loss.grad(self.w, Xa, y)
                grad_norm = np.linalg.norm(full_grad)
                loss_val = self.loss.value(self.w, Xa, y)

                # Ранний выход при расходимости: не отравляем историю
                if not (np.isfinite(grad_norm) and np.isfinite(loss_val)):
                    break

                self.history["loss"].append(loss_val)
                self.history["grad_norm"].append(grad_norm)

                if X_val is not None:
                    Xv_mdl = self._augment(X_val)
                    self.history["val_loss"].append(
                        self.loss.value(self.w, Xv_mdl, y_val)
                    )

                if k_mdl % cond_every == 0:
                    try:
                        H_mdl = self.loss.hessian(self.w, Xa, y)
                        if H_mdl is None:
                            self.history["cond"].append(np.inf)
                        else:
                            eigvals = np.linalg.eigvalsh(H_mdl)
                            lo = max(eigvals[0], 1e-15)
                            hi = eigvals[-1]
                            self.history["cond"].append(
                                hi / lo if hi > 0 else np.inf
                            )
                    except Exception:
                        self.history["cond"].append(np.inf)

                if grad_norm < eps:
                    self.converged_ = True
                    break

                if self.optimizer.uses_batches():
                    bs_mdl = self.optimizer.batch_size
                    idx_mdl = np.random.choice(
                        len(y), size=min(bs_mdl, len(y)),
                        replace=False,
                    )
                    grad_mdl = self.loss.grad(
                        self.w, Xa[idx_mdl], y[idx_mdl]
                    )
                else:
                    grad_mdl = full_grad

                self.w = self.optimizer.step(self.w, grad_mdl)

            self.n_iter_ = k_mdl + 1
            return self

        def predict(self, X):
            return self._augment(X) @ self.w

    return (LinearRegressionModel,)


@app.cell(hide_code=True)
def _(mo):
    mo.md(r"""
    ### 2.4.1 MSE
    $$Q(w)=\frac{1}{2m}\|Xw-y\|_2^2,\quad
    \nabla Q=\frac{1}{m}X^T(Xw-y),\quad
    H=\frac{1}{m}X^TX.$$
    """)
    return


@app.cell
def _(LossBase, np):
    class MSELoss(LossBase):
        def value(self, w, X, y):
            r = X @ w - y
            return 0.5 * np.dot(r, r) / len(y)
        def grad(self, w, X, y):
            r = X @ w - y
            return X.T @ r / len(y)
        def hessian(self, w, X, y):
            return X.T @ X / len(y)

    return (MSELoss,)


@app.cell(hide_code=True)
def _(mo):
    mo.md(r"""
    ### 2.4.2 MAE
    $$Q(w)=\frac{1}{m}\|Xw-y\|_1,\quad
    \nabla Q=\frac{1}{m}X^T\mathrm{sign}(Xw-y).$$
    Недифференцируема при $x_i^Tw=y_i$. Гессиан $=0$.
    """)
    return


@app.cell
def _(LossBase, np):
    class MAELoss(LossBase):
        def value(self, w, X, y):
            return np.mean(np.abs(X @ w - y))
        def grad(self, w, X, y):
            return X.T @ np.sign(X @ w - y) / len(y)
        def hessian(self, w, X, y):
            return np.zeros((X.shape[1], X.shape[1]))

    return (MAELoss,)


@app.cell(hide_code=True)
def _(mo):
    mo.md(r"""
    ### 2.4.3 Huber
    $$Q_{\text{Huber}}(w) = \frac{1}{m}\sum_{i=1}^{m}
        \begin{cases}
        \tfrac{1}{2} r_i^2, & |r_i| \le \delta,\\
        \delta\left(|r_i| - \tfrac{1}{2}\delta\right), & |r_i| > \delta,
        \end{cases}
        \quad r_i = x_i^\top w - y_i$$
    """)
    return


@app.cell
def _(LossBase, np):
    class HuberLoss(LossBase):
        def __init__(self, delta=1.0):
            self.delta = delta
        def value(self, w, X, y):
            r = X @ w - y
            abs_r = np.abs(r)
            vals = np.where(abs_r <= self.delta,
                            0.5 * r ** 2,
                            self.delta * (abs_r - 0.5 * self.delta))
            return np.mean(vals)
        def grad(self, w, X, y):
            r = X @ w - y
            return X.T @ np.clip(r, -self.delta, self.delta) / len(y)
        def hessian(self, w, X, y):
            r = X @ w - y
            mask = (np.abs(r) <= self.delta).astype(float)
            return X.T @ np.diag(mask) @ X / len(y)

    return (HuberLoss,)


@app.cell(hide_code=True)
def _(mo):
    mo.md(r"""
    ## 2.5 Методы оптимизации
    """)
    return


@app.cell
def _(OptimizerBase):
    class GD(OptimizerBase):
        def __init__(self, lr=0.01):
            self.lr = lr
        def step(self, w, grad = 0):
            return w - self.lr * grad

    return (GD,)


@app.cell
def _(OptimizerBase, np):
    class Momentum(OptimizerBase):
        def __init__(self, lr=0.01, beta=0.9):
            self.lr = lr; self.beta = beta; self.v = None
        def step(self, w, grad):
            if self.v is None or self.v.shape != w.shape:
                self.v = np.zeros_like(w)
            self.v = self.beta * self.v + grad
            return w - self.lr * self.v

    return (Momentum,)


@app.cell
def _(OptimizerBase, np):
    class Adam(OptimizerBase):
        def __init__(self, lr=0.01, beta1=0.9, beta2=0.999, eps=1e-8):
            self.lr = lr; self.beta1 = beta1; self.beta2 = beta2
            self.eps = eps; self.m = None; self.v = None; self.t = 0
        def step(self, w, grad):
            if self.m is None or self.m.shape != w.shape:
                self.m = np.zeros_like(w)
                self.v = np.zeros_like(w)
                self.t = 0
            self.t += 1
            self.m = self.beta1 * self.m + (1 - self.beta1) * grad
            self.v = self.beta2 * self.v + (1 - self.beta2) * grad ** 2
            m_hat = self.m / (1 - self.beta1 ** self.t)
            v_hat = self.v / (1 - self.beta2 ** self.t)
            return w - self.lr * m_hat / (np.sqrt(v_hat) + self.eps)

    return (Adam,)


@app.cell
def _(OptimizerBase):
    class MiniBatchSGD(OptimizerBase):
        def __init__(self, lr=0.01, batch_size=64):
            self.lr = lr; self.batch_size = batch_size
        def step(self, w, grad):
            return w - self.lr * grad
        def uses_batches(self):
            return True

    return (MiniBatchSGD,)


@app.cell
def _(np):
    def initial_condition_number(loss, X, y, fit_intercept=True):
        if fit_intercept:
            Xa = np.hstack([np.ones((X.shape[0], 1)), X])
        else:
            Xa = X
        H = loss.hessian(np.zeros(Xa.shape[1]), Xa, y)
        if H is None or np.allclose(H, 0):
            return np.inf
        eig = np.linalg.eigvalsh(H)
        hi, lo = eig[-1], eig[0]
        if hi <= 0 or lo <= 0:
            return np.inf
        return hi / lo

    return (initial_condition_number,)


@app.cell
def _(LinearRegressionModel, np):
    def tune_learning_rate(loss, opt_class, opt_kwargs,
                            X_tr, y_tr, X_va, y_va,
                            lr_grid, max_iter=300):
        best_tl = {"lr": None, "val_loss": np.inf}
        results_tl = []
        for lr_tl in lr_grid:
            opt_tl = opt_class(lr=lr_tl, **opt_kwargs)
            model_tl = LinearRegressionModel(loss, opt_tl)
            model_tl.fit(X_tr, y_tr, max_iter=max_iter)
            Xv_tl = model_tl._augment(X_va)
            val_loss_tl = loss.value(model_tl.w, Xv_tl, y_va)

            # Пропускаем NaN / inf — иначе сравнение ломается
            if not np.isfinite(val_loss_tl):
                results_tl.append(
                    {"lr": lr_tl, "val_loss": float("nan")}
                )
                continue

            results_tl.append(
                {"lr": lr_tl, "val_loss": float(val_loss_tl)}
            )
            if val_loss_tl < best_tl["val_loss"]:
                best_tl = {
                    "lr": lr_tl, "val_loss": float(val_loss_tl),
                }

        # Fallback: если все lr дали NaN/inf
        if best_tl["lr"] is None:
            fallback_lr = lr_grid[0] if lr_grid else 1e-3
            best_tl = {
                "lr": fallback_lr, "val_loss": float("inf"),
            }
        return best_tl, results_tl

    return (tune_learning_rate,)


@app.cell(hide_code=True)
def _(mo):
    mo.md(r"""
    ## 2.6.3 Оценка обусловленности задачи
    """)
    return


@app.cell
def _(
    HuberLoss,
    MAELoss,
    MSELoss,
    X_sc_tr,
    X_un_tr,
    initial_condition_number,
    pd,
    y_tr,
):
    losses_demo = {
        "MSE": MSELoss(),
        "MAE": MAELoss(),
        "Huber": HuberLoss(delta=1.0),
    }

    cond_rows = []
    for name_cd, loss_cd in losses_demo.items():
        k_un_cd = initial_condition_number(
            loss_cd, X_un_tr, y_tr
        )
        k_sc_cd = initial_condition_number(
            loss_cd, X_sc_tr, y_tr
        )
        cond_rows.append({
            "Функционал": name_cd,
            "κ(H), unscaled": k_un_cd,
            "κ(H), scaled": k_sc_cd,
        })
    cond_table = pd.DataFrame(cond_rows).set_index("Функционал")
    cond_table
    return


@app.cell(hide_code=True)
def _(mo):
    mo.md(r"""
    ## 2.6 Обучение на немасштабированных данных
    """)
    return


@app.cell
def _(Adam, GD, HuberLoss, MAELoss, MSELoss, MiniBatchSGD, Momentum):
    losses_set = {
        "MSE": MSELoss(),
        "MAE": MAELoss(),
        "Huber": HuberLoss(delta=1.0),
    }
    optimizers_set = {
        "GD": (GD, {}),
        "Momentum": (Momentum, {"beta": 0.9}),
        "Adam": (Adam, {"beta1": 0.9, "beta2": 0.999}),
        "MiniBatchSGD": (MiniBatchSGD, {"batch_size": 64}),
    }
    lr_grid = [1e-5, 1e-4, 1e-3, 1e-2, 1e-1, 1.0]
    return losses_set, lr_grid, optimizers_set


@app.cell
def _(
    X_un_tr,
    X_un_va,
    losses_set,
    lr_grid,
    optimizers_set,
    pd,
    tune_learning_rate,
    y_tr,
    y_va,
):
    tune_rows_un = []
    best_lr_un = {}
    for loss_name_un, loss_obj_un in losses_set.items():
        for opt_name_un, (opt_cls_un, opt_kw_un) in optimizers_set.items():
            best_un, _res_un = tune_learning_rate(
                loss_obj_un, opt_cls_un, opt_kw_un,
                X_un_tr, y_tr, X_un_va, y_va,
                lr_grid=lr_grid, max_iter=300,
            )
            best_lr_un[(loss_name_un, opt_name_un)] = best_un["lr"]
            tune_rows_un.append({
                "Функционал": loss_name_un,
                "Оптимизатор": opt_name_un,
                "best lr": best_un["lr"],
                "val_loss": best_un["val_loss"],
            })
    tune_un_df = pd.DataFrame(tune_rows_un)
    tune_un_df
    return (best_lr_un,)


@app.cell
def _(
    LinearRegressionModel,
    X_un_tr,
    X_un_va,
    best_lr_un,
    losses_set,
    optimizers_set,
    y_tr,
    y_va,
):
    final_un = {}
    for (loss_name_fu, opt_name_fu), lr_fu in best_lr_un.items():
        loss_obj_fu = losses_set[loss_name_fu]
        opt_cls_fu, opt_kw_fu = optimizers_set[opt_name_fu]
        opt_fu = opt_cls_fu(lr=lr_fu, **opt_kw_fu)
        model_fu = LinearRegressionModel(loss_obj_fu, opt_fu)
        model_fu.fit(
            X_un_tr, y_tr, eps=1e-6, max_iter=3000,
            X_val=X_un_va, y_val=y_va, cond_every=20,
        )
        final_un[(loss_name_fu, opt_name_fu)] = model_fu
        print(
            f"{loss_name_fu:6s} {opt_name_fu:12s} lr={lr_fu:.1e}  "
            f"iters={model_fu.n_iter_:5d}  "
            f"converged={model_fu.converged_}  "
            f"loss={model_fu.history['loss'][-1]:.4f}  "
            f"|grad|={model_fu.history['grad_norm'][-1]:.2e}"
        )
    return (final_un,)


@app.cell
def _(final_un, plt):
    keys_pu = list(final_un.keys())
    n_pu = len(keys_pu)
    fig_pu, axes_pu = plt.subplots(
        n_pu, 3, figsize=(15, 3.2 * n_pu)
    )
    if n_pu == 1:
        axes_pu = axes_pu.reshape(1, -1)

    for row_pu, key_pu in enumerate(keys_pu):
        model_pu = final_un[key_pu]
        hist_pu = model_pu.history

        axes_pu[row_pu, 0].plot(hist_pu["grad_norm"], color="C0")
        axes_pu[row_pu, 0].axhline(
            1e-6, color="red", linestyle="--", label="eps=1e-6"
        )
        axes_pu[row_pu, 0].set_yscale("log")
        axes_pu[row_pu, 0].set_title(f"{key_pu} — |∇Q|")
        axes_pu[row_pu, 0].set_xlabel("k")
        axes_pu[row_pu, 0].legend(fontsize=8)

        axes_pu[row_pu, 1].plot(hist_pu["loss"], color="C2")
        axes_pu[row_pu, 1].set_title(f"{key_pu} — Q(w)")
        axes_pu[row_pu, 1].set_xlabel("k")

        if len(hist_pu["cond"]) > 0:
            axes_pu[row_pu, 2].plot(hist_pu["cond"], color="C3")
            axes_pu[row_pu, 2].set_yscale("log")
            axes_pu[row_pu, 2].set_title(f"{key_pu} — κ(H)")
            axes_pu[row_pu, 2].set_xlabel("k")
        else:
            axes_pu[row_pu, 2].text(
                0.5, 0.5, "κ(H) = ∞", ha="center", va="center"
            )
            axes_pu[row_pu, 2].set_title(f"{key_pu} — κ(H)")

    plt.tight_layout()
    fig_pu
    return


@app.cell
def _(X_un_te, final_un, mean_squared_error, np, pd, y_te):
    rows_qu = []
    for (loss_name_qu, opt_name_qu), model_qu in final_un.items():
        y_pred_qu = model_qu.predict(X_un_te)
        rmse_log_qu = np.sqrt(
            mean_squared_error(y_te, y_pred_qu)
        )
        rmse_price_qu = np.sqrt(
            mean_squared_error(np.exp(y_te), np.exp(y_pred_qu))
        )
        rows_qu.append({
            "Функционал": loss_name_qu,
            "Оптимизатор": opt_name_qu,
            "RMSE (log)": round(rmse_log_qu, 4),
            "RMSE (price, руб.)": round(rmse_price_qu, 1),
            "iters": model_qu.n_iter_,
            "converged": model_qu.converged_,
        })
    quality_un = pd.DataFrame(rows_qu)
    quality_un
    return (quality_un,)


@app.cell(hide_code=True)
def _(mo):
    mo.md(r"""
    ## 2.7 Сравнение с моделями `scikit-learn`
    """)
    return


@app.cell
def _(
    HuberRegressor,
    LinearRegression,
    X_un_te,
    X_un_tr,
    mean_squared_error,
    np,
    pd,
    y_te,
    y_tr,
):
    sk_rows = []

    sk_lr = LinearRegression()
    sk_lr.fit(X_un_tr, y_tr)
    y_hat_lr = sk_lr.predict(X_un_te)
    sk_rows.append({
        "Функционал": "MSE",
        "Модель": "sklearn LinearRegression",
        "RMSE (log)": round(
            np.sqrt(mean_squared_error(y_te, y_hat_lr)), 4
        ),
        "RMSE (price, руб.)": round(
            np.sqrt(mean_squared_error(
                np.exp(y_te), np.exp(y_hat_lr)
            )), 1
        ),
    })

    sk_hub = HuberRegressor(epsilon=1.0, max_iter=1000)
    sk_hub.fit(X_un_tr, y_tr)
    y_hat_hub = sk_hub.predict(X_un_te)
    sk_rows.append({
        "Функционал": "Huber",
        "Модель": "sklearn HuberRegressor",
        "RMSE (log)": round(
            np.sqrt(mean_squared_error(y_te, y_hat_hub)), 4
        ),
        "RMSE (price, руб.)": round(
            np.sqrt(mean_squared_error(
                np.exp(y_te), np.exp(y_hat_hub)
            )), 1
        ),
    })

    sk_un_df = pd.DataFrame(sk_rows)
    sk_un_df
    return


@app.cell(hide_code=True)
def _(mo):
    mo.md(r"""
    ## 2.8 Обучение на масштабированных данных
    """)
    return


@app.cell
def _(
    X_sc_tr,
    X_sc_va,
    losses_set,
    lr_grid,
    optimizers_set,
    pd,
    tune_learning_rate,
    y_tr,
    y_va,
):
    tune_rows_sc = []
    best_lr_sc = {}
    for loss_name_ts, loss_obj_ts in losses_set.items():
        for opt_name_ts, (opt_cls_ts, opt_kw_ts) in optimizers_set.items():
            best_ts, _res_ts = tune_learning_rate(
                loss_obj_ts, opt_cls_ts, opt_kw_ts,
                X_sc_tr, y_tr, X_sc_va, y_va,
                lr_grid=lr_grid, max_iter=300,
            )
            best_lr_sc[(loss_name_ts, opt_name_ts)] = best_ts["lr"]
            tune_rows_sc.append({
                "Функционал": loss_name_ts,
                "Оптимизатор": opt_name_ts,
                "best lr": best_ts["lr"],
                "val_loss": best_ts["val_loss"],
            })
    tune_sc_df = pd.DataFrame(tune_rows_sc)
    tune_sc_df
    return (best_lr_sc,)


@app.cell
def _(
    LinearRegressionModel,
    X_sc_tr,
    X_sc_va,
    best_lr_sc,
    losses_set,
    optimizers_set,
    y_tr,
    y_va,
):
    final_sc = {}
    for (loss_name_fs, opt_name_fs), lr_fs in best_lr_sc.items():
        loss_obj_fs = losses_set[loss_name_fs]
        opt_cls_fs, opt_kw_fs = optimizers_set[opt_name_fs]
        opt_fs = opt_cls_fs(lr=lr_fs, **opt_kw_fs)
        model_fs = LinearRegressionModel(loss_obj_fs, opt_fs)
        model_fs.fit(
            X_sc_tr, y_tr, eps=1e-6, max_iter=3000,
            X_val=X_sc_va, y_val=y_va, cond_every=20,
        )
        final_sc[(loss_name_fs, opt_name_fs)] = model_fs
        print(
            f"{loss_name_fs:6s} {opt_name_fs:12s} lr={lr_fs:.1e}  "
            f"iters={model_fs.n_iter_:5d}  "
            f"converged={model_fs.converged_}  "
            f"loss={model_fs.history['loss'][-1]:.4f}  "
            f"|grad|={model_fs.history['grad_norm'][-1]:.2e}"
        )
    return (final_sc,)


@app.cell
def _(final_sc, plt):
    keys_ps = list(final_sc.keys())
    n_ps = len(keys_ps)
    fig_ps, axes_ps = plt.subplots(
        n_ps, 3, figsize=(15, 3.2 * n_ps)
    )
    if n_ps == 1:
        axes_ps = axes_ps.reshape(1, -1)

    for row_ps, key_ps in enumerate(keys_ps):
        model_ps = final_sc[key_ps]
        hist_ps = model_ps.history

        axes_ps[row_ps, 0].plot(hist_ps["grad_norm"], color="C0")
        axes_ps[row_ps, 0].axhline(
            1e-6, color="red", linestyle="--", label="eps=1e-6"
        )
        axes_ps[row_ps, 0].set_yscale("log")
        axes_ps[row_ps, 0].set_title(f"{key_ps} — |∇Q|")
        axes_ps[row_ps, 0].set_xlabel("k")
        axes_ps[row_ps, 0].legend(fontsize=8)

        axes_ps[row_ps, 1].plot(hist_ps["loss"], color="C2")
        axes_ps[row_ps, 1].set_title(f"{key_ps} — Q(w)")
        axes_ps[row_ps, 1].set_xlabel("k")

        if len(hist_ps["cond"]) > 0:
            axes_ps[row_ps, 2].plot(hist_ps["cond"], color="C3")
            axes_ps[row_ps, 2].set_yscale("log")
            axes_ps[row_ps, 2].set_title(f"{key_ps} — κ(H)")
            axes_ps[row_ps, 2].set_xlabel("k")
        else:
            axes_ps[row_ps, 2].text(
                0.5, 0.5, "κ(H) = ∞", ha="center", va="center"
            )
            axes_ps[row_ps, 2].set_title(f"{key_ps} — κ(H)")

    plt.tight_layout()
    fig_ps
    return


@app.cell
def _(X_sc_te, final_sc, mean_squared_error, np, pd, y_te):
    rows_qs = []
    for (loss_name_qs, opt_name_qs), model_qs in final_sc.items():
        y_pred_qs = model_qs.predict(X_sc_te)

            # RMSE в лог-шкале — только если прогнозы конечны
        if np.all(np.isfinite(y_pred_qs)):
            rmse_log_qs = float(np.sqrt(
                mean_squared_error(y_te, y_pred_qs)
            ))
        else:
            rmse_log_qs = float("nan")

        # RMSE в рублях — только если exp не уходит в inf
        y_true_price_qs = np.exp(y_te)
        y_pred_price_qs = np.exp(
            np.clip(y_pred_qs, -700.0, 700.0)
        )

        if (np.all(np.isfinite(y_pred_price_qs))
                and np.all(np.isfinite(y_true_price_qs))
                and np.isfinite(rmse_log_qs)):
            rmse_price_qs = float(np.sqrt(
                mean_squared_error(y_true_price_qs, y_pred_price_qs)
            ))
        else:
            rmse_price_qs = float("nan")

        rows_qs.append({
                "Функционал": loss_name_qs,
                "Оптимизатор": opt_name_qs,
                "RMSE (log)": round(rmse_log_qs, 4) if np.isfinite(rmse_log_qs) else None,
                "RMSE (price, руб.)": round(rmse_price_qs, 1) if np.isfinite(rmse_price_qs) else None,
                "iters": model_qs.n_iter_,
                "converged": model_qs.converged_,
        })

    quality_sc = pd.DataFrame(rows_qs)
    quality_sc
    return (quality_sc,)


@app.cell(hide_code=True)
def _(mo):
    mo.md(r"""
    ## Сравнение результатов до и после масштабирования
    """)
    return


@app.cell
def _(pd, quality_sc, quality_un):
    qa = quality_un.copy()
    qa["Версия"] = "unscaled"
    qb = quality_sc.copy()
    qb["Версия"] = "scaled"
    compare = pd.concat([qa, qb], ignore_index=True)
    compare = compare[["Функционал", "Оптимизатор", "Версия",
                       "RMSE (log)", "iters", "converged"]]
    compare
    return (compare,)


@app.cell
def _(compare, plt):
    pivot_iters = compare.pivot_table(
        index=["Функционал", "Оптимизатор"],
        columns="Версия",
        values="iters",
    )
    fig_it, ax_it = plt.subplots(figsize=(10, 4))
    pivot_iters.plot(kind="bar", ax=ax_it, logy=True)
    ax_it.set_ylabel("Число итераций (log)")
    ax_it.set_title("Итерации до сходимости: unscaled vs scaled")
    plt.tight_layout()
    fig_it
    return


@app.cell
def _(compare, plt):
    pivot_rmse = compare.pivot_table(
        index=["Функционал", "Оптимизатор"],
        columns="Версия",
        values="RMSE (log)",
    )
    fig_rm, ax_rm = plt.subplots(figsize=(10, 4))
    pivot_rmse.plot(kind="bar", ax=ax_rm)
    ax_rm.set_ylabel("RMSE (log)")
    ax_rm.set_title("Качество на тесте: unscaled vs scaled")
    plt.tight_layout()
    fig_rm
    return


@app.cell(hide_code=True)
def _(mo):
    mo.md(r"""
    ## Итоговые выводы

    ### Обусловленность
    - `unscaled`: κ(H) ~ 10^5…10^6 → овражный ландшафт.
    - `scaled`: κ(H) ~ 10…100 → быстрая сходимость.
    - MAE: H = 0, κ = ∞.

    ### Функционалы
    - **MSE** — гладкий, чувствителен к выбросам.
    - **MAE** — недифференцируем в точках остатка-нуля.
    - **Huber** — гладкий, устойчив к выбросам.

    ### Оптимизаторы
    - GD требует хорошо подобранного шага.
    - Momentum ускоряет движение по оврагу.
    - Adam лучше всех работает на unscaled.
    - Mini-batch SGD вносит шум, но быстро стартует.

    ### Главный вывод
    Масштабирование уменьшает κ(H) на 3–4 порядка и в десятки раз
    ускоряет сходимость.
    """)
    return


if __name__ == "__main__":
    app.run()
