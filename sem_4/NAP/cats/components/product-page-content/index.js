import { ProductComponent } from "../product-page-component/index.js"
import { ProductChars } from "../product-page-chars/index.js"
import { BackButtonComponent } from "../productpage-back-button/index.js"
import { MainPage } from "../../pages/main/index.js"
import { ThreeDModelComponent } from '../3d-model/index.js';

export class ProductContent {
    constructor(parent, root) {
        this.root = root
        this.parent = parent
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
                <div style="margin: 10px 0 5px 0; text-align: center; font-size: 20px;">3D-модель</div>
                <div id="model-container" style="margin: 20px 0; max-width: 1280px;"></div>
            `
        )
    }

    getBackButtonData() {
        return [
            {
                text: "Назад"
            },
            {
                text: "Купить"
            }
        ]
    }

    clickBack() {
        const mainPage = new MainPage(this.root)
        mainPage.render()
    }

    render(data) {
        const html = this.getHTML()
        this.parent.insertAdjacentHTML('beforeend', html)

        const component = new ProductComponent(this.pageRoot)
        component.render(data)

        const chars = new ProductChars(this.pageRoot)
        chars.render(data)

        const backButtonData = this.getBackButtonData()
        backButtonData.forEach((item) => {
            const backButton = new BackButtonComponent(this.pageRootBottom)
            backButton.render(item, this.clickBack.bind(this))
        })

        const modelContainer = document.getElementById('model-container');
        if (modelContainer) {
            this.threeDModel = new ThreeDModelComponent(modelContainer, '/cats/models/solar.glb');
            this.threeDModel.render();
        }
    }
}