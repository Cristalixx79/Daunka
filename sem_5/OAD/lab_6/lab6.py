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
    # Лабораторная работа №6
    ## L1- и L2-регуляризация, аналитические решения и анализ оптимизации

    Продолжение ЛР №5. Используется тот же датасет «продажа квартир»
    (`data/house_prices.csv`, генерируется `dataset.py`).
    """)
    return


@app.cell
def _():
    import os
    import numpy as np
    import pandas as pd
    import matplotlib.pyplot as plt
    import seaborn as sns
    from abc import ABC, abstractmethod

    from sklearn.linear_model import Lasso, Ridge, LinearRegression
    from sklearn.preprocessing import RobustScaler
    from sklearn.model_selection import train_test_split
    from sklearn.impute import SimpleImputer
    from sklearn.metrics import mean_squared_error

    sns.set_theme(style="ticks")
    np.random.seed(42)
    return (
        ABC,
        Lasso,
        Ridge,
        RobustScaler,
        SimpleImputer,
        abstractmethod,
        mean_squared_error,
        np,
        pd,
        plt,
        sns,
        train_test_split,
    )


@app.cell
def _():
    target_col_l6 = "log_price"
    return (target_col_l6,)


@app.cell
def _(pd):
    data_path_l6 = "data/house_prices.csv"

    df_raw_l6 = pd.read_csv(data_path_l6)
    print(f"Размер исходного набора: {df_raw_l6.shape}")
    df_raw_l6.head()
    return (df_raw_l6,)


@app.cell(hide_code=True)
def _(mo):
    mo.md(r"""
    ## 2.1 Математическое описание регуляризации

    $$R_{L1}(w) = \lambda \|w\|_1, \qquad R_{L2}(w) = \frac{\lambda}{2} \|w\|_2^2,
    \qquad F(w) = Q(w) + R(w).$$

    ### L1
    $$\frac{\partial R_{L1}}{\partial w_j} = \lambda\,\mathrm{sign}(w_j),\quad
    \nabla R_{L1}(w) = \lambda\,\mathrm{sign}(w).$$
    В точках $w_j = 0$ производная **не существует** (субградиент $[-1,1]$).
    Вторая производная $\partial^2 R_{L1}/\partial w_j^2 = 0$ при $w_j \neq 0$;
    в нуле не существует.

    ### L2
    $$\nabla R_{L2}(w) = \lambda w, \qquad H_{L2}(w) = \lambda I.$$
    Всюду дважды дифференцируем, гессиан положительно определён при $\lambda>0$.

    Для полного функционала: $\nabla F = \nabla Q + \nabla R$, $H_F = H_Q + H_R$.
    """)
    return


@app.cell
def _(ABC, abstractmethod, np):
    class LossBase(ABC):
        @abstractmethod
        def value(self, w, X, y): ...
        @abstractmethod
        def grad(self, w, X, y): ...
        @abstractmethod
        def hessian(self, w, X, y): ...

    class OptimizerBase(ABC):
        @abstractmethod
        def step(self, w, grad): ...
        def uses_batches(self):
            return False

    class RegularizerBase(ABC):
        def __init__(self, lam=0.0, fit_intercept=True):
            self.lam = float(lam)
            self.fit_intercept = fit_intercept

        def _mask(self, n):
            m = np.ones(n)
            if self.fit_intercept and n > 0:
                m[0] = 0.0
            return m

        @abstractmethod
        def value(self, w): ...
        @abstractmethod
        def grad(self, w): ...
        @abstractmethod
        def hessian(self, w): ...

    class NoRegularizer(RegularizerBase):
        def value(self, w):
            return 0.0
        def grad(self, w):
            return np.zeros_like(w)
        def hessian(self, w):
            return np.zeros((w.size, w.size))

    class L1Regularizer(RegularizerBase):
        def value(self, w):
            return self.lam * np.sum(np.abs(w) * self._mask(w.size))
        def grad(self, w):
            return self.lam * np.sign(w) * self._mask(w.size)
        def hessian(self, w):
            return np.zeros((w.size, w.size))

    class L2Regularizer(RegularizerBase):
        def value(self, w):
            return 0.5 * self.lam * np.sum((w ** 2) * self._mask(w.size))
        def grad(self, w):
            return self.lam * w * self._mask(w.size)
        def hessian(self, w):
            return self.lam * np.diag(self._mask(w.size))

    class RegularizedLoss:
        def __init__(self, base_loss, regularizer):
            self.base_loss = base_loss
            self.regularizer = regularizer
        def value(self, w, X, y):
            return self.base_loss.value(w, X, y) + self.regularizer.value(w)
        def grad(self, w, X, y):
            return self.base_loss.grad(w, X, y) + self.regularizer.grad(w)
        def hessian(self, w, X, y):
            return self.base_loss.hessian(w, X, y) + self.regularizer.hessian(w)

    return (
        L1Regularizer,
        L2Regularizer,
        LossBase,
        NoRegularizer,
        OptimizerBase,
        RegularizedLoss,
    )


@app.cell
def _(np):
    class LinearRegressionModel:
        def __init__(self, loss, optimizer, fit_intercept=True):
            self.loss = loss
            self.optimizer = optimizer
            self.fit_intercept = fit_intercept
            self.w = None
            self.history = {"loss": [], "grad_norm": [], "cond": [], "val_loss": []}
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
            self.history = {"loss": [], "grad_norm": [], "cond": [], "val_loss": []}
            self.converged_ = False

            for k_mdl in range(max_iter):
                full_grad = self.loss.grad(self.w, Xa, y)
                grad_norm = np.linalg.norm(full_grad)
                loss_val = self.loss.value(self.w, Xa, y)
                if not (np.isfinite(grad_norm) and np.isfinite(loss_val)):
                    break

                self.history["loss"].append(loss_val)
                self.history["grad_norm"].append(grad_norm)
                if X_val is not None:
                    Xv = self._augment(X_val)
                    self.history["val_loss"].append(
                        self.loss.value(self.w, Xv, y_val)
                    )

                if k_mdl % cond_every == 0:
                    try:
                        H = self.loss.hessian(self.w, Xa, y)
                        if H is None:
                            self.history["cond"].append(np.inf)
                        else:
                            eigvals = np.linalg.eigvalsh(H)
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
                    bs = self.optimizer.batch_size
                    idx = np.random.choice(len(y), size=min(bs, len(y)), replace=False)
                    grad = self.loss.grad(self.w, Xa[idx], y[idx])
                else:
                    grad = full_grad

                self.w = self.optimizer.step(self.w, grad)

            self.n_iter_ = k_mdl + 1
            return self

        def predict(self, X):
            return self._augment(X) @ self.w

    return (LinearRegressionModel,)


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

    class MAELoss(LossBase):
        def value(self, w, X, y):
            return np.mean(np.abs(X @ w - y))
        def grad(self, w, X, y):
            return X.T @ np.sign(X @ w - y) / len(y)
        def hessian(self, w, X, y):
            return np.zeros((X.shape[1], X.shape[1]))

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

    return HuberLoss, MAELoss, MSELoss


@app.cell
def _(OptimizerBase, np):
    class GD(OptimizerBase):
        def __init__(self, lr=0.01):
            self.lr = lr
        def step(self, w, grad):
            return w - self.lr * grad

    class Momentum(OptimizerBase):
        def __init__(self, lr=0.01, beta=0.9):
            self.lr = lr; self.beta = beta; self.v = None
        def step(self, w, grad):
            if self.v is None or self.v.shape != w.shape:
                self.v = np.zeros_like(w)
            self.v = self.beta * self.v + grad
            return w - self.lr * self.v

    class Adam(OptimizerBase):
        def __init__(self, lr=0.01, beta1=0.9, beta2=0.999, eps=1e-8):
            self.lr = lr; self.beta1 = beta1; self.beta2 = beta2
            self.eps = eps; self.m = None; self.v = None; self.t = 0
        def step(self, w, grad):
            if self.m is None or self.m.shape != w.shape:
                self.m = np.zeros_like(w); self.v = np.zeros_like(w); self.t = 0
            self.t += 1
            self.m = self.beta1 * self.m + (1 - self.beta1) * grad
            self.v = self.beta2 * self.v + (1 - self.beta2) * grad ** 2
            m_hat = self.m / (1 - self.beta1 ** self.t)
            v_hat = self.v / (1 - self.beta2 ** self.t)
            return w - self.lr * m_hat / (np.sqrt(v_hat) + self.eps)

    class MiniBatchSGD(OptimizerBase):
        def __init__(self, lr=0.01, batch_size=64):
            self.lr = lr; self.batch_size = batch_size
        def step(self, w, grad):
            return w - self.lr * grad
        def uses_batches(self):
            return True

    class RMSProp(OptimizerBase):
        def __init__(self, lr=0.01, beta=0.9, eps=1e-8):
            self.lr = lr; self.beta = beta; self.eps = eps; self.v = None
        def step(self, w, grad):
            if self.v is None or self.v.shape != w.shape:
                self.v = np.zeros_like(w)
            self.v = self.beta * self.v + (1 - self.beta) * grad ** 2
            return w - self.lr * grad / (np.sqrt(self.v) + self.eps)

    return GD, RMSProp


@app.cell
def _(SimpleImputer, df_raw_l6):
    df_clean_l6 = df_raw_l6.copy()
    cont_imp_l6 = ["area_m2", "distance_km", "income_k", "age_years"]
    df_clean_l6[cont_imp_l6] = SimpleImputer(strategy="median").fit_transform(
        df_clean_l6[cont_imp_l6]
    )
    for c_l6 in ["city", "condition"]:
        df_clean_l6[c_l6] = df_clean_l6[c_l6].fillna("Неизвестно")
    df_clean_l6["city"] = df_clean_l6["city"].replace("?", "Неизвестно")
    print(f"Пропусков после заполнения: {df_clean_l6.isna().sum().sum()}")
    return (df_clean_l6,)


@app.cell
def _(df_clean_l6, np):
    df_out_l6 = df_clean_l6.copy()

    def clip_iqr_l6(df, col, k=1.5):
        q1_l6 = df[col].quantile(0.25)
        q3_l6 = df[col].quantile(0.75)
        iqr_l6 = q3_l6 - q1_l6
        return np.clip(df[col], q1_l6 - k * iqr_l6, q3_l6 + k * iqr_l6)

    df_out_l6.loc[
        (df_out_l6["age_years"] < 0) | (df_out_l6["age_years"] > 100),
        "age_years",
    ] = np.nan
    df_out_l6["age_years"] = df_out_l6["age_years"].fillna(
        df_out_l6["age_years"].median()
    )
    for cc_l6 in ["area_m2", "income_k", "distance_km"]:
        df_out_l6[cc_l6] = clip_iqr_l6(df_out_l6, cc_l6)
    df_out_l6["price"] = clip_iqr_l6(df_out_l6, "price", k=3)
    df_out_l6[["area_m2", "age_years", "distance_km",
                "income_k", "price"]].describe().T
    return (df_out_l6,)


@app.cell
def _(df_out_l6, np, pd):
    df_feat_new_l6 = df_out_l6.copy()
    df_feat_new_l6["area_per_room"] = (
        df_feat_new_l6["area_m2"] / df_feat_new_l6["rooms"]
    )
    df_feat_new_l6["income_distance"] = (
        df_feat_new_l6["income_k"] / (df_feat_new_l6["distance_km"] + 1)
    )
    df_feat_new_l6["is_old"] = (df_feat_new_l6["age_years"] > 40).astype(int)
    df_feat_new_l6["log_price"] = np.log(df_feat_new_l6["price"])

    cond_map_l6 = {"Неизвестно": -1, "требует ремонта": 0,
                   "хорошее": 1, "отличное": 2}
    df_feat_new_l6["condition_ord"] = (
        df_feat_new_l6["condition"].map(cond_map_l6)
    )
    city_d_l6 = pd.get_dummies(
        df_feat_new_l6["city"], prefix="city", drop_first=True
    ).astype(int)
    df_feat_new_l6 = pd.concat([df_feat_new_l6, city_d_l6], axis=1)
    df_feat_new_l6 = df_feat_new_l6.drop(
        columns=["id", "city", "condition", "price"]
    )
    print(f"Признаковое пространство до линеаризации: {df_feat_new_l6.shape}")
    df_feat_new_l6.head()
    return (df_feat_new_l6,)


@app.cell
def _(df_feat_new_l6, plt, sns, target_col_l6):
    corr_before_l6 = (
        df_feat_new_l6.corr(numeric_only=True)[target_col_l6]
        .sort_values(ascending=False)
    )
    fig_corr_before, ax_corr_before = plt.subplots(figsize=(10, 8))
    sns.heatmap(
        df_feat_new_l6.corr(numeric_only=True),
        cmap="coolwarm", center=0, ax=ax_corr_before,
    )
    ax_corr_before.set_title("Корреляционная матрица до линеаризации")
    plt.tight_layout()
    corr_before_l6, fig_corr_before
    return (corr_before_l6,)


@app.cell(hide_code=True)
def _(mo):
    mo.md(r"""
    **Линеаризация.** Выбраны три нелинейных зависимости:
    `log_area = log(area_m2)`, `inv_distance = 1/(distance_km+1)`,
    `log_age = log1p(age_years)`. Исходные признаки сохраняются.
    """)
    return


@app.cell
def _(df_feat_new_l6, np):
    df_feat_full_l6 = df_feat_new_l6.copy()
    df_feat_full_l6["log_area"] = np.log(
        df_feat_full_l6["area_m2"].clip(lower=1e-6)
    )
    df_feat_full_l6["inv_distance"] = 1.0 / (
        df_feat_full_l6["distance_km"] + 1.0
    )
    df_feat_full_l6["log_age"] = np.log1p(
        df_feat_full_l6["age_years"].clip(lower=0)
    )
    print(f"Итоговое признаковое пространство: {df_feat_full_l6.shape}")
    return (df_feat_full_l6,)


@app.cell
def _(corr_before_l6, df_feat_full_l6, pd, target_col_l6):
    corr_after_l6 = (
        df_feat_full_l6.corr(numeric_only=True)[target_col_l6]
        .sort_values(ascending=False)
    )
    corr_compare_l6 = pd.DataFrame({
        "до линеаризации": corr_before_l6,
        "после линеаризации": corr_after_l6,
    })
    corr_compare_l6
    return


@app.cell
def _(df_feat_full_l6, plt, sns):
    fig_hm_after, ax_hm_after = plt.subplots(figsize=(10, 8))
    sns.heatmap(
        df_feat_full_l6.corr(numeric_only=True),
        cmap="coolwarm", center=0, ax=ax_hm_after,
    )
    ax_hm_after.set_title("Корреляционная матрица после линеаризации")
    plt.tight_layout()
    fig_hm_after
    return


@app.cell
def _(RobustScaler, df_feat_full_l6, np, target_col_l6, train_test_split):
    feature_cols_l6 = [
        c for c in df_feat_full_l6.columns if c != target_col_l6
    ]
    X_all_l6 = df_feat_full_l6[feature_cols_l6].values
    y_all_l6 = df_feat_full_l6[target_col_l6].values

    continuous_l6 = [
        "area_m2", "age_years", "distance_km", "income_k",
        "area_per_room", "income_distance",
        "log_area", "inv_distance", "log_age",
    ]
    cont_idx_l6 = [feature_cols_l6.index(c) for c in continuous_l6]

    X_unscaled_l6 = X_all_l6.copy()
    X_scaled_l6 = X_all_l6.copy()
    X_scaled_l6[:, cont_idx_l6] = RobustScaler().fit_transform(
        X_all_l6[:, cont_idx_l6]
    )

    idx_all_l6 = np.arange(len(y_all_l6))
    idx_tv_l6, idx_te_l6 = train_test_split(
        idx_all_l6, test_size=0.2, random_state=42
    )
    idx_tr_l6, idx_va_l6 = train_test_split(
        idx_tv_l6, test_size=0.25, random_state=42
    )

    X_un_tr = X_unscaled_l6[idx_tr_l6]
    X_un_va = X_unscaled_l6[idx_va_l6]
    X_un_te = X_unscaled_l6[idx_te_l6]
    X_sc_tr = X_scaled_l6[idx_tr_l6]
    X_sc_va = X_scaled_l6[idx_va_l6]
    X_sc_te = X_scaled_l6[idx_te_l6]
    y_tr = y_all_l6[idx_tr_l6]
    y_va = y_all_l6[idx_va_l6]
    y_te = y_all_l6[idx_te_l6]

    print(f"Train: {len(y_tr)}, Val: {len(y_va)}, Test: {len(y_te)}")
    print(f"Число признаков: {len(feature_cols_l6)}")
    return X_sc_te, X_sc_tr, X_sc_va, feature_cols_l6, y_te, y_tr, y_va


@app.cell
def _(GD, L1Regularizer, LinearRegressionModel, MSELoss, RegularizedLoss, np):
    def fit_l1_gd(X, y, lam, lr, eps=1e-6, max_iter=3000, eps_w=None,
                  X_val=None, y_val=None):
        loss_obj = RegularizedLoss(
            MSELoss(), L1Regularizer(lam=lam, fit_intercept=True)
        )
        model_obj = LinearRegressionModel(loss_obj, GD(lr=lr))
        Xa = model_obj._augment(X)
        w = np.zeros(Xa.shape[1])
        hist = {"loss": [], "grad_norm": [], "val_loss": []}
        converged = False
        k = 0

        for k in range(max_iter):
            full_grad = loss_obj.grad(w, Xa, y)
            grad_norm = np.linalg.norm(full_grad)
            loss_val = loss_obj.value(w, Xa, y)

            # Защита от расходимости
            if not (np.isfinite(grad_norm) and np.isfinite(loss_val)):
                break

            hist["loss"].append(loss_val)
            hist["grad_norm"].append(grad_norm)
            if X_val is not None:
                Xv = model_obj._augment(X_val)
                hist["val_loss"].append(MSELoss().value(w, Xv, y_val))

            if grad_norm < eps:
                converged = True
                break

            w = w - lr * full_grad
            if eps_w is not None:
                w[1:] = np.where(np.abs(w[1:]) < eps_w, 0.0, w[1:])

        model_obj.w = w
        model_obj.history = hist
        model_obj.n_iter_ = k + 1
        model_obj.converged_ = converged
        return model_obj

    return (fit_l1_gd,)


@app.cell
def _(MSELoss, X_sc_tr, X_sc_va, fit_l1_gd, np, pd, y_tr, y_va):
    lam_grid_l1 = [1e-5, 1e-4, 1e-3, 1e-2, 1e-1, 1.0, 10.0]
    lr_grid_l1 = [1e-4, 1e-3, 1e-2, 1e-1]

    best_l1 = {"lam": None, "lr": None, "val": np.inf}
    rows_l1 = []

    for lam_l1 in lam_grid_l1:
        for lr_l1 in lr_grid_l1:
            m_l1 = fit_l1_gd(
                X_sc_tr, y_tr,
                lam=lam_l1, lr=lr_l1, eps=1e-6, max_iter=500,
            )
            val_l1 = MSELoss().value(m_l1.w, m_l1._augment(X_sc_va), y_va)
            rows_l1.append({"lam": lam_l1, "lr": lr_l1, "val_mse": val_l1})
            if np.isfinite(val_l1) and val_l1 < best_l1["val"]:
                best_l1 = {"lam": lam_l1, "lr": lr_l1, "val": float(val_l1)}

    # Fallback, если все val = NaN/Inf
    if best_l1["lam"] is None:
        best_l1 = {"lam": 1e-3, "lr": 1e-3, "val": np.inf}

    best_l1_params = best_l1
    pd.DataFrame(rows_l1).sort_values("val_mse").head()
    return (best_l1_params,)


@app.cell
def _(
    X_sc_te,
    X_sc_tr,
    best_l1_params,
    fit_l1_gd,
    mean_squared_error,
    np,
    y_te,
    y_tr,
):
    model_l1_no_zero = fit_l1_gd(
        X_sc_tr, y_tr,
        lam=best_l1_params["lam"],
        lr=best_l1_params["lr"],
        eps=1e-6, max_iter=3000, eps_w=None,
    )
    rmse_l1_no_zero = np.sqrt(
        mean_squared_error(y_te, model_l1_no_zero.predict(X_sc_te))
    )
    print(
        f"L1 без зануления: lam={best_l1_params['lam']}, "
        f"lr={best_l1_params['lr']}, iters={model_l1_no_zero.n_iter_}, "
        f"converged={model_l1_no_zero.converged_}, "
        f"RMSE={rmse_l1_no_zero:.6f}"
    )
    return model_l1_no_zero, rmse_l1_no_zero


@app.cell
def _(MSELoss, X_sc_tr, X_sc_va, best_l1_params, fit_l1_gd, np, y_tr, y_va):
    eps_grid_l6 = [1e-5, 1e-4, 1e-3]
    best_eps_l6 = {"eps_w": None, "val": np.inf}

    for eps_w_l6 in eps_grid_l6:
        m_eps_l6 = fit_l1_gd(
            X_sc_tr, y_tr,
            lam=best_l1_params["lam"],
            lr=best_l1_params["lr"],
            eps=1e-6, max_iter=500, eps_w=eps_w_l6,
        )
        val_eps_l6 = MSELoss().value(
            m_eps_l6.w, m_eps_l6._augment(X_sc_va), y_va
        )
        if np.isfinite(val_eps_l6) and val_eps_l6 < best_eps_l6["val"]:
            best_eps_l6 = {
                "eps_w": eps_w_l6, "val": float(val_eps_l6),
            }

    best_eps_w = best_eps_l6["eps_w"]
    print(f"Выбранное ε_w = {best_eps_w}")
    return (best_eps_w,)


@app.cell
def _(
    X_sc_te,
    X_sc_tr,
    best_eps_w,
    best_l1_params,
    fit_l1_gd,
    mean_squared_error,
    np,
    y_te,
    y_tr,
):
    model_l1_zero = fit_l1_gd(
        X_sc_tr, y_tr,
        lam=best_l1_params["lam"],
        lr=best_l1_params["lr"],
        eps=1e-6, max_iter=3000,
        eps_w=best_eps_w if best_eps_w is not None else None,
    )
    rmse_l1_zero = np.sqrt(
        mean_squared_error(y_te, model_l1_zero.predict(X_sc_te))
    )
    print(
        f"L1 с занулением: ε_w={best_eps_w}, "
        f"iters={model_l1_zero.n_iter_}, "
        f"converged={model_l1_zero.converged_}, "
        f"RMSE={rmse_l1_zero:.6f}"
    )
    return model_l1_zero, rmse_l1_zero


@app.cell
def _(
    Lasso,
    X_sc_te,
    X_sc_tr,
    X_sc_va,
    mean_squared_error,
    np,
    y_te,
    y_tr,
    y_va,
):
    lam_grid_lasso = [1e-5, 1e-4, 1e-3, 1e-2, 1e-1, 1.0, 10.0]
    best_lasso = {"lam": None, "val": np.inf}

    for lam_lasso in lam_grid_lasso:
        m_lasso = Lasso(alpha=lam_lasso, max_iter=20000, tol=1e-4)
        m_lasso.fit(X_sc_tr, y_tr)
        val_lasso = mean_squared_error(y_va, m_lasso.predict(X_sc_va))
        if np.isfinite(val_lasso) and val_lasso < best_lasso["val"]:
            best_lasso = {"lam": lam_lasso, "val": float(val_lasso)}

    if best_lasso["lam"] is None:
        best_lasso = {"lam": 1e-3, "val": np.inf}

    lasso_model = Lasso(
        alpha=best_lasso["lam"], max_iter=20000, tol=1e-4
    ).fit(X_sc_tr, y_tr)
    rmse_lasso = np.sqrt(
        mean_squared_error(y_te, lasso_model.predict(X_sc_te))
    )
    print(
        f"Lasso: alpha={best_lasso['lam']}, "
        f"RMSE={rmse_lasso:.6f}, "
        f"нулевых: {np.sum(np.abs(lasso_model.coef_) < 1e-8)}"
    )
    return best_lasso, lasso_model, rmse_lasso


@app.cell
def _(
    best_eps_w,
    best_l1_params,
    best_lasso,
    feature_cols_l6,
    lasso_model,
    model_l1_no_zero,
    model_l1_zero,
    np,
    pd,
    rmse_l1_no_zero,
    rmse_l1_zero,
    rmse_lasso,
):
    names_l1_coef = ["intercept"] + feature_cols_l6
    coef_df_l1 = pd.DataFrame({
        "feature": names_l1_coef,
        "L1_no_zero": model_l1_no_zero.w,
        "L1_zero": model_l1_zero.w,
        "Lasso": np.r_[lasso_model.intercept_, lasso_model.coef_],
    })
    quality_l1 = pd.DataFrame([
        {"model": "L1 GD без зануления", "RMSE": rmse_l1_no_zero,
         "lam": best_l1_params["lam"], "lr": best_l1_params["lr"]},
        {"model": "L1 GD с занулением", "RMSE": rmse_l1_zero,
         "lam": best_l1_params["lam"], "lr": best_l1_params["lr"],
         "eps_w": best_eps_w},
        {"model": "Lasso sklearn", "RMSE": rmse_lasso,
         "lam": best_lasso["lam"]},
    ])
    coef_df_l1, quality_l1
    return


@app.cell
def _(feature_cols_l6, lasso_model, model_l1_no_zero, model_l1_zero, np):
    def small_features_l1(w, names, thr=1e-8):
        return [n for n, v in zip(names, w) if abs(v) < thr]

    names_zi = ["intercept"] + feature_cols_l6
    zero_info_l1 = {
        "L1_no_zero |w|<1e-8": small_features_l1(
            model_l1_no_zero.w, names_zi
        ),
        "L1_zero == 0": small_features_l1(
            model_l1_zero.w, names_zi, thr=1e-12
        ),
        "Lasso |w|<1e-8": small_features_l1(
            np.r_[lasso_model.intercept_, lasso_model.coef_], names_zi
        ),
    }
    for k_zi, v_zi in zero_info_l1.items():
        print(f"\n{k_zi}: {len(v_zi)}")
        print(v_zi)
    return


@app.cell
def _(df_feat_full_l6, feature_cols_l6, lasso_model, plt, sns, target_col_l6):
    selected_lasso = [
        f for f, c in zip(feature_cols_l6, lasso_model.coef_)
        if abs(c) > 1e-8
    ]
    corr_selected_l6 = (
        df_feat_full_l6[selected_lasso + [target_col_l6]].corr()
    )
    fig_corr_sel, ax_corr_sel = plt.subplots(figsize=(10, 8))
    sns.heatmap(corr_selected_l6, cmap="coolwarm", center=0, ax=ax_corr_sel)
    ax_corr_sel.set_title("Корреляционная структура после отбора Lasso")
    plt.tight_layout()
    selected_lasso, fig_corr_sel
    return


@app.cell(hide_code=True)
def _(mo):
    mo.md(r"""
    ## 2.4 L2-регуляризация и анализ оптимизации
    ### 2.4.1 Аналитическое решение OLS
    $$w^* = (X^T X)^{-1} X^T y \quad(\text{через } \texttt{lstsq}).$$
    """)
    return


@app.cell
def _(X_sc_te, X_sc_tr, mean_squared_error, np, y_te, y_tr):
    def fit_ols_analytical(X, y, fit_intercept=True):
        Xa = (np.hstack([np.ones((X.shape[0], 1)), X])
              if fit_intercept else X)
        w, *_ = np.linalg.lstsq(Xa, y, rcond=None)
        return w

    w_ols = fit_ols_analytical(X_sc_tr, y_tr)
    Xa_te_ols = np.hstack([np.ones((X_sc_te.shape[0], 1)), X_sc_te])
    y_pred_ols = Xa_te_ols @ w_ols
    rmse_ols = np.sqrt(mean_squared_error(y_te, y_pred_ols))
    print(
        f"OLS analytical: RMSE={rmse_ols:.6f}, "
        f"|w|={np.linalg.norm(w_ols):.4f}"
    )
    return rmse_ols, w_ols


@app.cell
def _(X_sc_te, X_sc_tr, X_sc_va, mean_squared_error, np, y_te, y_tr, y_va):
    def fit_ridge_analytical(X, y, lam, fit_intercept=True):
        Xa = (np.hstack([np.ones((X.shape[0], 1)), X])
              if fit_intercept else X)
        mask = np.ones(Xa.shape[1])
        if fit_intercept:
            mask[0] = 0.0
        if lam <= 0:
            w, *_ = np.linalg.lstsq(Xa, y, rcond=None)
            return w
        A = Xa.T @ Xa + lam * np.diag(mask)
        b = Xa.T @ y
        return np.linalg.solve(A, b)

    lam_grid_rga = [1e-5, 1e-4, 1e-3, 1e-2, 1e-1, 1.0, 10.0]
    best_ridge = {"lam": None, "val": np.inf}
    for lam_rga in lam_grid_rga:
        w_rga = fit_ridge_analytical(X_sc_tr, y_tr, lam=lam_rga)
        Xv_rga = np.hstack([np.ones((X_sc_va.shape[0], 1)), X_sc_va])
        val_rga = mean_squared_error(y_va, Xv_rga @ w_rga)
        if np.isfinite(val_rga) and val_rga < best_ridge["val"]:
            best_ridge = {"lam": lam_rga, "val": float(val_rga)}
    if best_ridge["lam"] is None:
        best_ridge = {"lam": 1e-3, "val": np.inf}

    best_ridge_lam = best_ridge["lam"]
    w_ridge_analytical = fit_ridge_analytical(
        X_sc_tr, y_tr, lam=best_ridge_lam
    )
    Xa_te_rga = np.hstack([np.ones((X_sc_te.shape[0], 1)), X_sc_te])
    rmse_ridge_analytical = np.sqrt(
        mean_squared_error(y_te, Xa_te_rga @ w_ridge_analytical)
    )
    print(
        f"Ridge analytical: lam={best_ridge_lam}, "
        f"RMSE={rmse_ridge_analytical:.6f}"
    )
    return best_ridge_lam, rmse_ridge_analytical, w_ridge_analytical


@app.cell
def _(
    feature_cols_l6,
    pd,
    rmse_ols,
    rmse_ridge_analytical,
    w_ols,
    w_ridge_analytical,
):
    compare_ols_ridge = pd.DataFrame({
        "feature": ["intercept"] + feature_cols_l6,
        "OLS": w_ols,
        "Ridge analytical": w_ridge_analytical,
    })
    compare_ols_ridge["diff"] = (
        compare_ols_ridge["Ridge analytical"] - compare_ols_ridge["OLS"]
    )
    quality_ols_ridge = pd.DataFrame([
        {"model": "OLS analytical", "RMSE": rmse_ols},
        {"model": "Ridge analytical", "RMSE": rmse_ridge_analytical},
    ])
    compare_ols_ridge, quality_ols_ridge
    return


@app.cell
def _(
    Ridge,
    X_sc_te,
    X_sc_tr,
    X_sc_va,
    mean_squared_error,
    np,
    y_te,
    y_tr,
    y_va,
):
    lam_grid_rsk = [1e-5, 1e-4, 1e-3, 1e-2, 1e-1, 1.0, 10.0]
    best_ridge_sk = {"lam": None, "val": np.inf}
    for lam_rsk in lam_grid_rsk:
        m_rsk = Ridge(alpha=lam_rsk, fit_intercept=True)
        m_rsk.fit(X_sc_tr, y_tr)
        val_rsk = mean_squared_error(y_va, m_rsk.predict(X_sc_va))
        if np.isfinite(val_rsk) and val_rsk < best_ridge_sk["val"]:
            best_ridge_sk = {"lam": lam_rsk, "val": float(val_rsk)}
    if best_ridge_sk["lam"] is None:
        best_ridge_sk = {"lam": 1e-3, "val": np.inf}

    ridge_sk = Ridge(
        alpha=best_ridge_sk["lam"], fit_intercept=True
    ).fit(X_sc_tr, y_tr)
    rmse_ridge_sk = np.sqrt(
        mean_squared_error(y_te, ridge_sk.predict(X_sc_te))
    )
    print(
        f"Ridge sklearn: alpha={best_ridge_sk['lam']}, "
        f"RMSE={rmse_ridge_sk:.6f}"
    )
    return best_ridge_sk, ridge_sk, rmse_ridge_sk


@app.cell
def _(
    best_ridge_lam,
    best_ridge_sk,
    feature_cols_l6,
    np,
    pd,
    ridge_sk,
    rmse_ridge_analytical,
    rmse_ridge_sk,
    w_ridge_analytical,
):
    compare_ridge = pd.DataFrame({
        "feature": ["intercept"] + feature_cols_l6,
        "Ridge analytical": w_ridge_analytical,
        "Ridge sklearn": np.r_[ridge_sk.intercept_, ridge_sk.coef_],
    })
    compare_ridge["diff"] = (
        compare_ridge["Ridge sklearn"]
        - compare_ridge["Ridge analytical"]
    )
    quality_ridge = pd.DataFrame([
        {"model": "Ridge analytical", "lam": best_ridge_lam,
         "RMSE": rmse_ridge_analytical},
        {"model": "Ridge sklearn", "lam": best_ridge_sk["lam"],
         "RMSE": rmse_ridge_sk},
    ])
    compare_ridge, quality_ridge
    return


@app.cell(hide_code=True)
def _(mo):
    mo.md(r"""
    ### 2.4.4 Влияние L2 на оптимизацию (RMSProp — новый оптимизатор)
    """)
    return


@app.cell
def _(
    HuberLoss,
    L2Regularizer,
    LinearRegressionModel,
    MAELoss,
    MSELoss,
    NoRegularizer,
    RMSProp,
    RegularizedLoss,
    X_sc_tr,
    X_sc_va,
    np,
    pd,
    y_tr,
    y_va,
):
    losses_set_l6 = {
        "MSE": MSELoss(),
        "MAE": MAELoss(),
        "Huber": HuberLoss(delta=1.0),
    }

    def tune_rmsprop_for_loss(base_loss, use_l2=False):
        lr_grid_rms = [1e-5, 1e-4, 1e-3, 1e-2, 1e-1]
        lam_grid_rms = (
            [1e-5, 1e-4, 1e-3, 1e-2, 1e-1, 1.0, 10.0]
            if use_l2 else [0.0]
        )
        best_rms = {"lr": None, "lam": None, "val": np.inf}
        rows_rms = []
        for lam_rms in lam_grid_rms:
            for lr_rms in lr_grid_rms:
                reg_rms = (
                    L2Regularizer(lam=lam_rms, fit_intercept=True)
                    if use_l2 else NoRegularizer()
                )
                loss_rms = RegularizedLoss(base_loss, reg_rms)
                opt_rms = RMSProp(lr=lr_rms, beta=0.9, eps=1e-8)
                model_rms = LinearRegressionModel(loss_rms, opt_rms)
                model_rms.fit(X_sc_tr, y_tr, eps=1e-6, max_iter=500)
                val_rms = base_loss.value(
                    model_rms.w, model_rms._augment(X_sc_va), y_va
                )
                rows_rms.append(
                    {"lam": lam_rms, "lr": lr_rms, "val": val_rms}
                )
                if np.isfinite(val_rms) and val_rms < best_rms["val"]:
                    best_rms = {
                        "lr": lr_rms, "lam": lam_rms,
                        "val": float(val_rms),
                    }
        if best_rms["lr"] is None:
            best_rms = {"lr": 1e-3, "lam": 0.0, "val": np.inf}
        return best_rms, rows_rms

    best_rmsprop = {}
    tune_rows_rms = []

    for loss_name_rms, base_loss_rms in losses_set_l6.items():
        best_no_rms, _ = tune_rmsprop_for_loss(base_loss_rms, use_l2=False)
        best_l2_rms, _ = tune_rmsprop_for_loss(base_loss_rms, use_l2=True)
        best_rmsprop[(loss_name_rms, False)] = best_no_rms
        best_rmsprop[(loss_name_rms, True)] = best_l2_rms
        tune_rows_rms.append({
            "loss": loss_name_rms, "mode": "no reg",
            "lr": best_no_rms["lr"], "lam": 0.0,
            "val": best_no_rms["val"],
        })
        tune_rows_rms.append({
            "loss": loss_name_rms, "mode": "L2",
            "lr": best_l2_rms["lr"], "lam": best_l2_rms["lam"],
            "val": best_l2_rms["val"],
        })

    pd.DataFrame(tune_rows_rms)
    return best_rmsprop, losses_set_l6


@app.cell
def _(
    L2Regularizer,
    LinearRegressionModel,
    NoRegularizer,
    RMSProp,
    RegularizedLoss,
    X_sc_tr,
    X_sc_va,
    best_rmsprop,
    losses_set_l6,
    y_tr,
    y_va,
):
    models_l2 = {}
    for loss_name_l2m, base_loss_l2m in losses_set_l6.items():
        for use_l2_l2m in [False, True]:
            params_l2m = best_rmsprop[(loss_name_l2m, use_l2_l2m)]
            reg_l2m = (
                L2Regularizer(lam=params_l2m["lam"], fit_intercept=True)
                if use_l2_l2m else NoRegularizer()
            )
            loss_l2m = RegularizedLoss(base_loss_l2m, reg_l2m)
            opt_l2m = RMSProp(lr=params_l2m["lr"], beta=0.9, eps=1e-8)
            model_l2m = LinearRegressionModel(loss_l2m, opt_l2m)
            model_l2m.fit(
                X_sc_tr, y_tr, eps=1e-6, max_iter=3000,
                X_val=X_sc_va, y_val=y_va, cond_every=20,
            )
            models_l2[(loss_name_l2m, use_l2_l2m)] = model_l2m
            print(
                f"{loss_name_l2m:6s} | "
                f"{'L2' if use_l2_l2m else 'no reg':6s} | "
                f"lr={params_l2m['lr']:.1e} | "
                f"lam={params_l2m['lam']:.1e} | "
                f"iters={model_l2m.n_iter_:5d} | "
                f"conv={model_l2m.converged_} | "
                f"|grad|={model_l2m.history['grad_norm'][-1]:.2e}"
            )
    return (models_l2,)


@app.cell
def _(losses_set_l6, models_l2, np, plt):
    n_losses_l2 = len(losses_set_l6)
    fig_l2, axes_l2 = plt.subplots(
        n_losses_l2, 3, figsize=(16, 4.2 * n_losses_l2)
    )
    if n_losses_l2 == 1:
        axes_l2 = axes_l2.reshape(1, -1)

    for i_l2, loss_name_plot in enumerate(losses_set_l6):
        for use_l2_plot, label_plot, color_plot in [
            (False, "без регуляризации", "C0"),
            (True, "L2", "C1"),
        ]:
            model_plot = models_l2[(loss_name_plot, use_l2_plot)]
            hist_plot = model_plot.history
            axes_l2[i_l2, 0].plot(
                hist_plot["grad_norm"], label=label_plot, color=color_plot
            )
            axes_l2[i_l2, 0].axhline(
                1e-6, color="red", linestyle="--", linewidth=1
            )
            axes_l2[i_l2, 0].set_yscale("log")
            axes_l2[i_l2, 0].set_title(f"{loss_name_plot}: ||∇F||")
            axes_l2[i_l2, 0].set_xlabel("k")
            axes_l2[i_l2, 0].legend(fontsize=8)

            axes_l2[i_l2, 1].plot(
                hist_plot["loss"], label=label_plot, color=color_plot
            )
            axes_l2[i_l2, 1].set_title(f"{loss_name_plot}: F(w)")
            axes_l2[i_l2, 1].set_xlabel("k")

            cond_plot = np.array(hist_plot["cond"], dtype=float)
            cond_plot[~np.isfinite(cond_plot)] = np.nan
            axes_l2[i_l2, 2].plot(
                cond_plot, label=label_plot, color=color_plot
            )
            axes_l2[i_l2, 2].set_yscale("log")
            axes_l2[i_l2, 2].set_title(f"{loss_name_plot}: κ(H)")
            axes_l2[i_l2, 2].set_xlabel("k")

    plt.tight_layout()
    fig_l2
    return


@app.cell
def _(X_sc_te, mean_squared_error, models_l2, np, pd, y_te):
    rows_q2 = []
    for (loss_name_q2, use_l2_q2), model_q2 in models_l2.items():
        y_pred_q2 = model_q2.predict(X_sc_te)
        rmse_q2 = np.sqrt(mean_squared_error(y_te, y_pred_q2))
        rows_q2.append({
            "loss": loss_name_q2,
            "mode": "L2" if use_l2_q2 else "no reg",
            "RMSE": rmse_q2,
            "iters": model_q2.n_iter_,
            "converged": model_q2.converged_,
        })
    quality_l2 = pd.DataFrame(rows_q2).sort_values(["loss", "mode"])
    quality_l2
    return


@app.cell(hide_code=True)
def _(mo):
    mo.md(r"""
    ## Итоговые выводы

    ### L1
    - GD-реализация L1 и `Lasso` дают согласованный отбор: часть
      признаков получает нулевые/малые коэффициенты.
    - Порог зануления $|w_j|<\varepsilon_w$ усиливает разреженность,
      но требует аккуратного выбора.

    ### L2
    - Аналитическое решение Ridge и `Ridge` sklearn совпадают.
    - L2 улучшает обусловленность: $\kappa(X^TX+\lambda I)<\kappa(X^TX)$.
    - Графики $\|\nabla F\|$, $F(w)$, $\kappa(H)$ показывают сглаживание
      ландшафта и ускорение RMSProp.

    ### Влияние на качество
    - Малые $\lambda$ почти не меняют RMSE, но стабилизируют решение.
    - Большие $\lambda$ вносят смещение и увеличивают RMSE.
    - Для MAE (гессиан $\equiv 0$) L2-добавка критична: она делает задачу
      корректно обусловленной.
    """)
    return


if __name__ == "__main__":
    app.run()
