export class ProductChars {
    constructor(parent) {
        this.parent = parent
    }

    getHTML(data) {
        const charsBody = `<div>Название: ${data.name}</div>
                    <div>Описание: ${data.description}</div>
                    <div>Производитель: ${data.vendor}</div>
                    <div>Цена: ${data.price}</div>`

        if (data.antibacterial) {
            return (
                `
                <div style="padding-left: 30px; display: flex; flex-direction: column">
                    ${charsBody}
                    <div>Антибактериальный компонент: Да</div>
                </div>
            `
            )
        }
        return (
            `
                <div style="padding-left: 30px; display: flex; flex-direction: column">
                    ${charsBody}
                </div>
            `
        )
    }

    render(data) {
        const html = this.getHTML(data)
       this.parent.insertAdjacentHTML('beforeend', html)
    }
}