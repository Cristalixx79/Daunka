import { ProductCardComponent } from "../main-page-product-card/index.js";
import { ProductPage } from "../../pages/product/index.js";
import { FilterForm } from "../filter-form/index.js";
import { ajax } from "../../modules/ajax.js";
import { stockUrls } from "../../modules/stockUrls.js";

export class Content {
    constructor(parent, root) {
        this.root = root
        this.parent = parent;
        this.hasActiveCard = true;
    }

    get pageRoot() {
        return document.getElementById('content-page')
    }

    get pageCarouselRoot() {
        return document.getElementById('carousel-inner')
    }

    get missingItemCard() {
        return {
            id: -1,
            src: "https://xltools.ru/static/15ffdca4da395b99352870a92397ded4/image-not-found.png",
            title: "Missing item",
            stock_text: ""
        }
    }

    getTitleBlock() {
        return (
            `
                <div style="max-width: 1000px;">
                    <h1 style="text-align: center; margin: 0; padding: 10px 0px; font-size: 30px; font-weight: 600; color: #FF525D;" >Производство красок и красителей</h1>
                    <div style="text-align: center;">Осуществляем доставку по всей России, Республике Беларусь, Республике Казахстан. Мы работаем с юридическими и с физическими лицами.
                        Вам остается только связаться с нами или с нашими дилерами, все остальное сделаем мы.</div>
                </div>
            `
        )
    }

    getPageRoot() {
        return (
            `<div id="content-page" style="display: flex; margin-top: 20px; width: 850px; gap: 1rem;"></div>`
        )
    }

    getPageCarouselRoot() {
        return (
            `
            <div id="carouselExampleIndicators" class="carousel slide" data-bs-ride="true">
                <div id="carousel-inner" class="carousel-inner"></div>
                <button style="height: 50%; top: 25%;" class="carousel-control-prev" type="button" data-bs-target="#carouselExampleIndicators" data-bs-slide="prev">
                    <span class="carousel-control-prev-icon" aria-hidden="true"></span>
                    <span class="visually-hidden">Предыдущий</span>
                </button>
                <button style="height: 50%; top: 25%;" class="carousel-control-next" type="button" data-bs-target="#carouselExampleIndicators" data-bs-slide="next">
                    <span class="carousel-control-next-icon" aria-hidden="true"></span>
                    <span class="visually-hidden">Следующий</span>
                </button>
            </div>
        `
        )
    }

    getData() {
        ajax.get(stockUrls.getStocks(), (data) => {
            this.renderData(data);
        })
    }

    getDataByName(title) {
        ajax.get(stockUrls.getStocksByTitle(title), (data) => {
            this.renderData(data, title);
        })
    }

    renderData(items, title) {
        if (items.length === 0) {
            const card = new ProductCardComponent(this.pageCarouselRoot, this.hasActiveCard)
            card.renderMissing(this.missingItemCard, title)
        }
        items.forEach((item) => {
            const card = new ProductCardComponent(this.pageCarouselRoot, this.hasActiveCard)
            card.render(item, this.clickCard.bind(this))
            this.hasActiveCard = false;
        })
    }

    clickCard(e) {
        let cardId = e.target.dataset.id
        const page = new ProductPage(this.root)
        page.render(cardId)
    }

    clickFilterFormSearch(e) {
        const filterFormInput = document.getElementById('filter-form-input')
        if (filterFormInput.value === '') return;

        document.getElementById('carousel-inner').innerHTML = ''
        this.hasActiveCard = true;
        this.getDataByName(filterFormInput.value);
    }

    clickFilterFormClean(e) {
        const filterFormInput = document.getElementById('filter-form-input')
        if (filterFormInput.value === '') return;

        document.getElementById('carousel-inner').innerHTML = ''
        this.hasActiveCard = true
        this.getData(filterFormInput.value)
        filterFormInput.value = ''
    }

    render() {
        const title = this.getTitleBlock()
        this.parent.insertAdjacentHTML('beforeend', title)

        const content = this.getPageRoot()
        this.parent.insertAdjacentHTML('beforeend', content)

        const carousel = this.getPageCarouselRoot()
        this.pageRoot.insertAdjacentHTML('beforeend', carousel)

        const filterForm = new FilterForm(this.pageRoot)
        filterForm.render(this.clickFilterFormSearch.bind(this), this.clickFilterFormClean.bind(this))
        
        this.getData();
    }
}