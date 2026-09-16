export class HeaderContent {
    constructor(parent, root) {
        this.root = root
        this.parent = parent;
    }

    get pageRoot() {
        return document.getElementById('header-content')
    }

    getHTML() {
        return (
            `
                <nav id="header-content" style="display: flex; justify-content: space-between; align-items: center; width: 100%; padding: 0px 40px;">
                    <a href="index.html" style="display: block; width: 50px; height: 50px; border-radius: 50%; background-color: white"></a>
                    <div style="display: flex;">
                        <a href="index.html" style="color: white; display: block; padding-right: 50px">Главная</a>
                        <a href="index.html" style="color: white; display: block;">О нас</a>
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