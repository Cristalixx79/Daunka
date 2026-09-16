export class FilterForm {
    constructor(parent, isActive) {
        this.parent = parent;
    }

    getHTML() {
        return (
            `
               <div style="display: flex; flex-direction: column; gap: 10px;">
                   <div>Введите название карточки</div>
                   <input id="filter-form-input">
                   <button id="filter-form-click-search" class="btn btn-primary">Поиск</button>
                   <button id="filter-form-click-clean" class="btn btn-primary">Сбросить</button>
               </div>
            `
        )
    }

    addListeners(listenerSearch, listenerClean) {
        document.getElementById(`filter-form-click-search`).addEventListener("click", listenerSearch)
        document.getElementById(`filter-form-click-clean`).addEventListener("click", listenerClean)
    }

    render(listenerSearch, listenerClean) {
        const html = this.getHTML()

        this.parent.insertAdjacentHTML('beforeend', html)
        this.addListeners(listenerSearch, listenerClean)
    }
}