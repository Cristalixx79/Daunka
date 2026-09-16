export class FooterContent {
    constructor(parent, root) {
        this.root = root
        this.parent = parent;
    }

    get pageRoot() {
        return document.getElementById('footer-content')
    }

    getHTML() {
        return (
            `
                <nav id="footer-content" style="display: flex; justify-content: space-between; align-items: center; width: 100%; padding: 0px 40px;">
                <div style="display: flex;">
                        <a href="#" style="color: gray; display: block; padding-right: 50px">Главная</a>
                        <a href="#" style="color: gray; display: block;">О нас</a>
                    </div>
                <div style="display: flex;">
                        <a href="#" style="color: gray; display: block; padding-right: 50px">Контактный телефон: +7-985-357-34-83</a>
                        <a href="#" style="color: gray; display: block;">Политика ДНД</a>
                    </div>
                </nav>
            `
        )
    }

    render() {
        const content = this.getHTML()
        this.parent.insertAdjacentHTML('beforeend', content)
    }
}