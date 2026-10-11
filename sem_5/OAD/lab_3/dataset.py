import numpy as np
import pandas as pd

def _make_demo_dataset(n=1500, seed=42):
    """Демо-данные «продажа квартир» с пропусками и выбросами всех видов."""
    rng = np.random.default_rng(seed)
    area = np.exp(rng.normal(4.0, 0.35, n))
    rooms = np.clip(np.round(area / 22 + rng.normal(0, 0.6, n)), 1, 6).astype(int)
    age = np.clip(rng.normal(25, 12, n), 0, None)
    dist = rng.gamma(2.0, 3.0, n)
    income = rng.normal(70, 15, n)
    city = rng.choice(
        ["Москва", "Санкт-Петербург", "Казань", "Самара"],
        size=n,
        p=[0.4, 0.3, 0.2, 0.1],
    ).astype(object)
    cond = rng.choice(
        ["отличное", "хорошее", "требует ремонта"],
        size=n,
        p=[0.25, 0.5, 0.25]
    ).astype(object)
    parking = rng.integers(0, 2, n)

    city_k = pd.Series(city).map(
        {"Москва": 1.6, "Санкт-Петербург": 1.2, "Казань": 0.9, "Самара": 0.8}
    ).to_numpy()
    cond_k = pd.Series(cond).map(
        {"отличное": 1.15, "хорошее": 1.0, "требует ремонта": 0.8}
    ).to_numpy()
    price = (
        150 * area * city_k * cond_k * (1 - 0.01 * dist)
        * np.exp(rng.normal(0, 0.2, n))
    )

    # --- выбросы: ошибки единиц измерения, «заглушки», экстремальные значения
    area[rng.choice(n, 8, replace=False)] *= 10
    age[rng.choice(n, 5, replace=False)] = -1
    age[rng.choice(n, 6, replace=False)] = 999
    income[rng.choice(n, 5, replace=False)] *= 5
    price[rng.choice(n, 6, replace=False)] *= 8

    # --- пропуски: MCAR / MAR / MNAR
    area[rng.random(n) < 0.03] = np.nan
    dist[rng.random(n) < 0.06] = np.nan
    income[rng.random(n) < 0.05 + 0.35 * (age > 35)] = np.nan          # MAR: зависит от возраста
    cond[rng.random(n) < 0.05 + 0.30 * (cond == "требует ремонта")] = np.nan  # MNAR
    city[rng.random(n) < 0.04] = np.nan
    city[rng.random(n) < 0.015] = "?"                                   # «скрытый» пропуск

    return pd.DataFrame({
        "id": np.arange(1, n + 1),
        "area_m2": area, "rooms": rooms, "age_years": age,
        "distance_km": dist, "income_k": income,
        "city": city, "condition": cond, "parking": parking,
        "price": price,
    })


if __name__ == "__main__":
    data = _make_demo_dataset()

    print(data.describe().T)
    data.to_csv(path_or_buf='data/house_prices.csv', index=False)