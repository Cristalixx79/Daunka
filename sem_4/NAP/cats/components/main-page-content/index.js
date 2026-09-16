import { ProductCardComponent } from "../main-page-product-card/index.js";
import { ProductPage } from "../../pages/product/index.js";

export class Content {
    constructor(parent, root) {
        this.root = root
        this.parent = parent;
    }

    get pageCarouselRoot() {
        return document.getElementById('carousel-inner')
    }

    getMainCarousel() {
        return (
            `
            <div style="display: flex; align-items: center; margin-top: 20px">
                <div style="font-size: 24px; font-weight: 600; color: black; padding-right: 30px">Наша продукция</div>
                <div id="carouselExampleIndicators" class="carousel slide" data-bs-ride="true">
                    <div id="carousel-inner" class="carousel-inner" style="width: 445px"></div>
                    <button class="carousel-control-prev" type="button" data-bs-target="#carouselExampleIndicators" data-bs-slide="prev">
                        <span class="carousel-control-prev-icon" aria-hidden="true"></span>
                        <span class="visually-hidden">Предыдущий</span>
                    </button>
                    <button class="carousel-control-next" type="button" data-bs-target="#carouselExampleIndicators" data-bs-slide="next">
                        <span class="carousel-control-next-icon" aria-hidden="true"></span>
                        <span class="visually-hidden">Следующий</span>
                    </button>
                </div>
            </div>
        `
        )
    }

    getTitle() {
        return (
            `
                <h1 style="text-align: center; margin: 0; padding: 10px 0px; font-size: 30px; font-weight: 600; color: #FF525D;" >Высокотехнологичное производство 
                    лабораторных работ по дисциплине "Программирование сетевых приложений"</h1>
                <div style="text-align: center;">Осуществляем доставку по всей России, Республике Беларусь, Республике Казахстан. Мы работаем с юридическими и с физическими лицами.
                    Вам остается только связаться с нами или с нашими дилерами, все остальное сделаем мы.</div>
            `
        )
    }

    getData() {
        return [
            {
                id: 1,
                name: "Белая краска",
                description: "Краска для тротуаров",
                vendor: "Arc painting",
                price: "1200 p",
                secondary: "11 мин.",
                antibacterial: false,
                active: "active"
            },
            {
                id: 2,
                name: "Голубая краска",
                description: "Краска для стен",
                vendor: "AntiCH",
                price: "900 p",
                secondary: "14 мин.",
                antibacterial: false,
                active: ""
            },
            {
                id: 3,
                name: "Жёлтая краска",
                description: "Краска для мебели",
                vendor: "Kribi Paste",
                price: "1500 p",
                secondary: "13 мин.",
                antibacterial: true,
                active: ""
            },
        ]
    }

    clickCard(e) {
        const cardId = e.target.dataset.id
        const data = this.getData()
        let index = 0
        for (index = 0; index < data.length; index++) {
            const element = data[index];
            if (element.id == cardId) {
                break
            }
        }

        const page = new ProductPage(this.root, data[index])
        page.render()
    }

    render() {
        const title = this.getTitle()
        this.parent.insertAdjacentHTML('beforeend', title)

        const carousel = this.getMainCarousel()
        this.parent.insertAdjacentHTML('beforeend', carousel)

        const data = this.getData()
        data.forEach((item) => {
            const card = new ProductCardComponent(this.pageCarouselRoot)
            card.render(item, this.clickCard.bind(this))
        })
    }
}