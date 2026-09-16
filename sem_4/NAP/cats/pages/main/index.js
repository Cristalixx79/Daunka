import { Content } from "../../components/main-page-content/index.js";
import { FooterContent } from "../../components/footer/index.js";
import { HeaderContent } from "../../components/header/index.js";

export class MainPage {
    constructor(parent) {
        this.parent = parent;
    }

    get pageRoot() {
        return document.getElementById('main-page')
    }

    get pageRootHeader() {
        return document.getElementById('header')
    }

    get pageRootFooter() {
        return document.getElementById('footer')
    }

    getHTML() {
        return (
            `
                <div id="main-page" class="d-flex flex-wrap" style="flex: 1; max-width: 1280px; flex-direction: column; align-items: center;"><div/>
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

    render() {
        this.parent.innerHTML = ''
        const header = this.getHTML_header()
        this.parent.insertAdjacentHTML('beforeend', header)
        const html = this.getHTML()
        this.parent.insertAdjacentHTML('beforeend', html)
        const footer = this.getHTML_footer()
        this.parent.insertAdjacentHTML('beforeend', footer)

        const headerContent = new HeaderContent(this.pageRootHeader, this.parent)
        headerContent.render()

        const content = new Content(this.pageRoot, this.parent)
        content.render()

        const footerContent = new FooterContent(this.pageRootFooter, this.parent)
        footerContent.render()
    }
}