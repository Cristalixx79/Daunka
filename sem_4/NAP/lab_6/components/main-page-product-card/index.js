export class ProductCardComponent {
    constructor(parent, isActive) {
        this.parent = parent;
        this.isActive = isActive;
    }

    getHTML(data) {
        let active = (this.isActive) ? "active" : "";
        return (
            `
            <div class="carousel-item ${active}">
                <div class="d-flex justify-content-center" style="gap: 1.5rem;">
                    <div class="card carousel-card shadow-sm">
                        <div style="max-height: 250px; overflow: hidden;">
                            <img src="${data.src}" class="card-img-top" style="width: 100%; height: 100%; object-fit: cover;" alt="...">
                        </div>
                        <div class="card-body">
                            <h5 class="card-title">${data.title}</h5>
                            <p class="card-text">${data.stock_text}</p>
                            <div class="d-flex justify-content-between align-items-center">
                                <small class="text-body-secondary">Добавлено ${(new Date(data.createdAt)).toLocaleString().substring(0, 10)}</small>
                                <div class="btn-group">
                                    <button class="btn btn-primary" id="click-card-${data.id}" data-id="${data.id}">Подробнее</button>
                                </div>
                            </div>
                        </div>
                    </div>
                </div>
            </div>
        `
        )
    }

    getHTMLMissing(data, title) {
        return (
            `
            <div class="carousel-item active">
                <div class="d-flex justify-content-center" style="gap: 1.5rem;">
                    <div class="card carousel-card shadow-sm">
                        <div style="max-height: 250px; overflow: hidden;">
                            <img src="${data.src}" class="card-img-top" style="width: 100%; height: 100%; object-fit: cover;" alt="...">
                        </div>
                        <div class="card-body">
                            <h5 class="card-title">По запросу "${title}" ничего не нашлось</h5>
                            <p class="card-text">Попробуйте заново</p>
                        </div>
                    </div>
                </div>
            </div>
            `
        )
    }

    addListeners(data, listener) {
        document.getElementById(`click-card-${data.id}`).addEventListener("click", listener)
    }

    render(data, listener) {
        const html = this.getHTML(data)

        this.parent.insertAdjacentHTML('beforeend', html)
        this.addListeners(data, listener)
    }

    renderMissing(data, title) {
        const html = this.getHTMLMissing(data, title)
        this.parent.insertAdjacentHTML('beforeend', html)
    }
}