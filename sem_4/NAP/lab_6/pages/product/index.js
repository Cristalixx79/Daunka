import { FooterContent } from "../../components/footer/index.js";
import { HeaderContent } from "../../components/header/index.js";
import { ProductContent } from "../../components/product-page-content/index.js";

export class ProductPage {
    constructor(parent) {
        this.parent = parent
    }

    get pageRoot() {
        return document.getElementById('product-page')
    }

    getHTML() {
        return (
            `
                <div id="product-page" style="flex: 1"></div>
            `
        )
    }
    getHTML_header() {
        return (
            `
                <header id="header" class="d-flex flex-wrap" style="justify-content: center; position: relative; height: 80px; min-width: 100vw; background-color: #090647;"><header/>
            `
        )
    }
    getHTML_footer() {
        return (
            `
                <footer id="footer" class="d-flex flex-wrap" style="height: 80px; min-width: 100vw; border-top: 1.5px solid #C3CDEB;"><footer/>
            `
        )
    }

    get pageRoot() {
        return document.getElementById('product-page')
    }

    get pageRootHeader() {
        return document.getElementById('header')
    }

    get pageRootFooter() {
        return document.getElementById('footer')
    }

    render(cardId) {
        this.parent.innerHTML = ''
        const header = this.getHTML_header()
        this.parent.insertAdjacentHTML('beforeend', header)
        const html = this.getHTML()
        this.parent.insertAdjacentHTML('beforeend', html)
        const footer = this.getHTML_footer()
        this.parent.insertAdjacentHTML('beforeend', footer)

        const headerContent = new HeaderContent(this.pageRootHeader, this.parent)
        headerContent.render()

        const productContent = new ProductContent(this.pageRoot, this.parent, cardId)
        productContent.render()

        const footerContent = new FooterContent(this.pageRootFooter, this.parent)
        footerContent.render()
    }
}