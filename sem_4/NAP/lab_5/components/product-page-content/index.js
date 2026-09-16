import { ProductComponent } from "../product-page-component/index.js"
import { ProductChars } from "../product-page-chars/index.js"
import { BackButtonComponent } from "../productpage-back-button/index.js"
import { DeleteButtonComponent } from "../product-page-delete-button/index.js"
import { MainPage } from "../../pages/main/index.js"
import { stockUrls } from "../../modules/stockUrls.js"
import { ajax } from "../../modules/ajax.js"

export class ProductContent {
    constructor(parent, root, cardId) {
        this.root = root
        this.parent = parent
        this.cardId = cardId
    }

    get pageRoot() {
        return document.getElementById('product-component')
    }
    get pageRootBottom() {
        return document.getElementById('product-component-bottom')
    }

    getHTML() {
        return (
            `  
                <div id="product-component" style="display: flex; max-width: 1280px; margin-top: 45px;"></div>
                <div id="product-component-bottom" style="margin-top: 20px; display: flex; justify-content: space-between; max-width: 1280px;"></div>
            `
        )
    }

    getData() {
        ajax.get(stockUrls.getStockById(this.cardId), (data) => {
            this.renderData(data);
        })
    }

    renderData(item) {
        const product = new ProductComponent(this.pageRoot)
        product.render(item)
    }

    clickBack() {
        const mainPage = new MainPage(this.root)
        mainPage.render()
    }

    clickDelete() {
        ajax.delete(stockUrls.removeStockById(this.cardId), () => {
            const mainPage = new MainPage(this.root)
            mainPage.render()
        })
    }

    render() {
        const html = this.getHTML()
        this.parent.insertAdjacentHTML('beforeend', html)

        this.getData()

        const backButton = new BackButtonComponent(this.pageRootBottom)
        backButton.render(this.clickBack.bind(this))

        const deleteButton = new DeleteButtonComponent(this.pageRootBottom)
        deleteButton.render(this.clickDelete.bind(this))
    }
}