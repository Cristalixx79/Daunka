export class ProductCardComponent {
    constructor(parent) {
        this.parent = parent;
    }

    getHTML(data) {
        return (
            `
            <div class="carousel-item ${data.active}" style="width: 445px">
                <div class="d-flex justify-content-center">
                    <div class="card shadow-sm">
                        <div style="height: 250px; overflow: hidden;">
                            <img src="../../img/2.jpg" class="card-img-top" style="width: 100%; height: 100%; object-fit: cover;" alt="...">
                        </div>
                        <div class="card-body">
                            <h5 class="card-title">${data.name}</h5>
                            <p class="card-text">${data.description}</p>
                            <div class="d-flex justify-content-between align-items-center">
                                <small class="text-body-secondary">${data.secondary}</small>
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

    addListeners(data, listener) {
        document.getElementById(`click-card-${data.id}`).addEventListener("click", listener)
    }

    render(data, listener) {
        const html = this.getHTML(data)
        this.parent.insertAdjacentHTML('beforeend', html)
        this.addListeners(data, listener)
    }
}