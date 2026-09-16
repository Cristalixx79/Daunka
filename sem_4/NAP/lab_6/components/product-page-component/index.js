export class ProductComponent {
    constructor(parent) {
        this.parent = parent
    }

    getHTML(data) {
        return (
            `
                <div class="card" style="width: 540px;">
                    <div class="row g-0">
                        <div class="col-md-4">
                            <img src="${data.src}" class="img-fluid" alt="картинка">
                        </div>
                        <div class="col-md-8">
                            <div class="card-body">
                                <h5 class="card-title">${data.title}</h5>
                                <div class="card-text">Описание: ${data.stock_text}</div>
                                <div class="card-text">Цена: ${(Math.random() * 1000).toLocaleString().substring(0, 3)} руб.</div>
                                <div style="margin-top: 23px" class="card-text">ID товара: <span style="font-size: 13px">${crypto.randomUUID()}</span></div>
                            </div>
                        </div>
                    </div>
                </div>
            `
        )
    }

    render(data) {
        const html = this.getHTML(data)
        this.parent.insertAdjacentHTML('beforeend', html)
    }
}