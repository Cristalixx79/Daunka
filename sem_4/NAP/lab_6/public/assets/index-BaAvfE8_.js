var e=(e,t)=>()=>(e&&(t=e(e=0)),t),t=(e,t)=>()=>(t||(e((t={exports:{}}).exports,t),e=null),t.exports);(function(){let e=document.createElement(`link`).relList;if(e&&e.supports&&e.supports(`modulepreload`))return;for(let e of document.querySelectorAll(`link[rel="modulepreload"]`))n(e);new MutationObserver(e=>{for(let t of e)if(t.type===`childList`)for(let e of t.addedNodes)e.tagName===`LINK`&&e.rel===`modulepreload`&&n(e)}).observe(document,{childList:!0,subtree:!0});function t(e){let t={};return e.integrity&&(t.integrity=e.integrity),e.referrerPolicy&&(t.referrerPolicy=e.referrerPolicy),e.crossOrigin===`use-credentials`?t.credentials=`include`:e.crossOrigin===`anonymous`?t.credentials=`omit`:t.credentials=`same-origin`,t}function n(e){if(e.ep)return;e.ep=!0;let n=t(e);fetch(e.href,n)}})();var n,r=e((()=>{n=class{constructor(e,t){this.parent=e,this.isActive=t}getHTML(e){return`
            <div class="carousel-item ${this.isActive?`active`:``}">
                <div class="d-flex justify-content-center" style="gap: 1.5rem;">
                    <div class="card carousel-card shadow-sm">
                        <div style="max-height: 250px; overflow: hidden;">
                            <img src="${e.src}" class="card-img-top" style="width: 100%; height: 100%; object-fit: cover;" alt="...">
                        </div>
                        <div class="card-body">
                            <h5 class="card-title">${e.title}</h5>
                            <p class="card-text">${e.stock_text}</p>
                            <div class="d-flex justify-content-between align-items-center">
                                <small class="text-body-secondary">Добавлено ${new Date(e.createdAt).toLocaleString().substring(0,10)}</small>
                                <div class="btn-group">
                                    <button class="btn btn-primary" id="click-card-${e.id}" data-id="${e.id}">Подробнее</button>
                                </div>
                            </div>
                        </div>
                    </div>
                </div>
            </div>
        `}getHTMLMissing(e,t){return`
            <div class="carousel-item active">
                <div class="d-flex justify-content-center" style="gap: 1.5rem;">
                    <div class="card carousel-card shadow-sm">
                        <div style="max-height: 250px; overflow: hidden;">
                            <img src="${e.src}" class="card-img-top" style="width: 100%; height: 100%; object-fit: cover;" alt="...">
                        </div>
                        <div class="card-body">
                            <h5 class="card-title">По запросу "${t}" ничего не нашлось</h5>
                            <p class="card-text">Попробуйте заново</p>
                        </div>
                    </div>
                </div>
            </div>
            `}addListeners(e,t){document.getElementById(`click-card-${e.id}`).addEventListener(`click`,t)}render(e,t){let n=this.getHTML(e);this.parent.insertAdjacentHTML(`beforeend`,n),this.addListeners(e,t)}renderMissing(e,t){let n=this.getHTMLMissing(e,t);this.parent.insertAdjacentHTML(`beforeend`,n)}}})),i,a=e((()=>{i=class{constructor(e,t){this.root=t,this.parent=e}get pageRoot(){return document.getElementById(`footer-content`)}getHTML(){return`
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
            `}render(){let e=this.getHTML();this.parent.insertAdjacentHTML(`beforeend`,e)}}})),o,s=e((()=>{o=class{constructor(e,t){this.root=t,this.parent=e}get pageRoot(){return document.getElementById(`header-content`)}getHTML(){return`
                <nav id="header-content" style="display: flex; justify-content: space-between; align-items: center; width: 100%; padding: 0px 40px;">
                    <a href="index.html" style="display: block; width: 50px; height: 50px; border-radius: 50%; background-color: white"></a>
                    <div style="display: flex;">
                        <a href="index.html" style="color: white; display: block; padding-right: 50px">Главная</a>
                        <a href="index.html" style="color: white; display: block;">О нас</a>
                    </div>
                </nav>
            `}render(){let e=this.getHTML();this.parent.insertAdjacentHTML(`beforeend`,e)}}})),c,l=e((()=>{c=class{constructor(e){this.parent=e}getHTML(e){return`
                <div class="card" style="width: 540px;">
                    <div class="row g-0">
                        <div class="col-md-4">
                            <img src="${e.src}" class="img-fluid" alt="картинка">
                        </div>
                        <div class="col-md-8">
                            <div class="card-body">
                                <h5 class="card-title">${e.title}</h5>
                                <div class="card-text">Описание: ${e.stock_text}</div>
                                <div class="card-text">Цена: ${(Math.random()*1e3).toLocaleString().substring(0,3)} руб.</div>
                                <div style="margin-top: 23px" class="card-text">ID товара: <span style="font-size: 13px">${crypto.randomUUID()}</span></div>
                            </div>
                        </div>
                    </div>
                </div>
            `}render(e){let t=this.getHTML(e);this.parent.insertAdjacentHTML(`beforeend`,t)}}})),u,d=e((()=>{u=class{constructor(e){this.parent=e}addListeners(e){document.getElementById(`back-button`).addEventListener(`click`,e)}getHTML(){return`
                <button id="back-button" class="btn btn-primary" type="button">Назад</button>
            `}render(e){let t=this.getHTML();this.parent.insertAdjacentHTML(`beforeend`,t),this.addListeners(e)}}})),f,p=e((()=>{f=class{constructor(e){this.parent=e}addListeners(e){document.getElementById(`delete-button`).addEventListener(`click`,e)}getHTML(){return`
                <button id="delete-button" class="btn btn-primary" type="button">Удалить карточку</button>
            `}render(e){let t=this.getHTML();this.parent.insertAdjacentHTML(`beforeend`,t),this.addListeners(e)}}})),m,h,g=e((()=>{m=class{constructor(){this.baseUrl=`http://localhost:3000`}getStocks(){return`${this.baseUrl}/stocks`}getStocksByTitle(e){return`${this.baseUrl}/stocks?title=${e}`}getStockById(e){return`${this.baseUrl}/stocks/${e}`}createStock(){return`${this.baseUrl}/stocks`}removeStockById(e){return`${this.baseUrl}/stocks/${e}`}updateStockById(e){return`${this.baseUrl}/stocks/${e}`}},h=new m})),_,v,y=e((()=>{_=class{async get(e,t){try{let n=await fetch(e);t(await this._parseResponse(n),n.status)}catch(e){console.error(`Ошибка GET запроса:`,e),t(null,0)}}async post(e,t,n){try{let r=await fetch(e,{method:`POST`,headers:{"Content-Type":`application/json`},body:JSON.stringify(t)});n(await this._parseResponse(r),r.status)}catch(e){console.error(`Ошибка POST запроса:`,e),n(null,0)}}async patch(e,t,n){try{let r=await fetch(e,{method:`PATCH`,headers:{"Content-Type":`application/json`},body:JSON.stringify(t)});n(await this._parseResponse(r),r.status)}catch(e){console.error(`Ошибка PATCH запроса:`,e),n(null,0)}}async delete(e,t){try{let n=await fetch(e,{method:`DELETE`});t(await this._parseResponse(n),n.status)}catch(e){console.error(`Ошибка DELETE запроса:`,e),t(null,0)}}async _parseResponse(e){let t=e.headers.get(`content-type`);if(t&&t.includes(`application/json`))try{return await e.json()}catch(e){return console.error(`Ошибка парсинга JSON:`,e),null}return null}},v=new _})),b,x=e((()=>{l(),d(),p(),k(),g(),y(),b=class{constructor(e,t,n){this.root=t,this.parent=e,this.cardId=n}get pageRoot(){return document.getElementById(`product-component`)}get pageRootBottom(){return document.getElementById(`product-component-bottom`)}getHTML(){return`  
                <div id="product-component" style="display: flex; max-width: 1280px; margin-top: 45px;"></div>
                <div id="product-component-bottom" style="margin-top: 20px; display: flex; justify-content: space-between; max-width: 1280px;"></div>
            `}getData(){v.get(h.getStockById(this.cardId),e=>{this.renderData(e)})}renderData(e){new c(this.pageRoot).render(e)}clickBack(){new O(this.root).render()}clickDelete(){v.delete(h.removeStockById(this.cardId),()=>{new O(this.root).render()})}render(){let e=this.getHTML();this.parent.insertAdjacentHTML(`beforeend`,e),this.getData(),new u(this.pageRootBottom).render(this.clickBack.bind(this)),new f(this.pageRootBottom).render(this.clickDelete.bind(this))}}})),S,C=e((()=>{a(),s(),x(),S=class{constructor(e){this.parent=e}get pageRoot(){return document.getElementById(`product-page`)}getHTML(){return`
                <div id="product-page" style="flex: 1"></div>
            `}getHTML_header(){return`
                <header id="header" class="d-flex flex-wrap" style="justify-content: center; position: relative; height: 80px; min-width: 100vw; background-color: #090647;"><header/>
            `}getHTML_footer(){return`
                <footer id="footer" class="d-flex flex-wrap" style="height: 80px; min-width: 100vw; border-top: 1.5px solid #C3CDEB;"><footer/>
            `}get pageRoot(){return document.getElementById(`product-page`)}get pageRootHeader(){return document.getElementById(`header`)}get pageRootFooter(){return document.getElementById(`footer`)}render(e){this.parent.innerHTML=``;let t=this.getHTML_header();this.parent.insertAdjacentHTML(`beforeend`,t);let n=this.getHTML();this.parent.insertAdjacentHTML(`beforeend`,n);let r=this.getHTML_footer();this.parent.insertAdjacentHTML(`beforeend`,r),new o(this.pageRootHeader,this.parent).render(),new b(this.pageRoot,this.parent,e).render(),new i(this.pageRootFooter,this.parent).render()}}})),w,T=e((()=>{w=class{constructor(e,t){this.parent=e}getHTML(){return`
               <div style="display: flex; flex-direction: column; gap: 10px;">
                   <div>Введите название карточки</div>
                   <input id="filter-form-input">
                   <button id="filter-form-click-search" class="btn btn-primary">Поиск</button>
                   <button id="filter-form-click-clean" class="btn btn-primary">Сбросить</button>
               </div>
            `}addListeners(e,t){document.getElementById(`filter-form-click-search`).addEventListener(`click`,e),document.getElementById(`filter-form-click-clean`).addEventListener(`click`,t)}render(e,t){let n=this.getHTML();this.parent.insertAdjacentHTML(`beforeend`,n),this.addListeners(e,t)}}})),E,D=e((()=>{r(),C(),T(),y(),g(),E=class{constructor(e,t){this.root=t,this.parent=e,this.hasActiveCard=!0}get pageRoot(){return document.getElementById(`content-page`)}get pageCarouselRoot(){return document.getElementById(`carousel-inner`)}get missingItemCard(){return{id:-1,src:`https://xltools.ru/static/15ffdca4da395b99352870a92397ded4/image-not-found.png`,title:`Missing item`,stock_text:``}}getTitleBlock(){return`
                <div style="max-width: 1000px;">
                    <h1 style="text-align: center; margin: 0; padding: 10px 0px; font-size: 30px; font-weight: 600; color: #FF525D;" >Производство красок и красителей</h1>
                    <div style="text-align: center;">Осуществляем доставку по всей России, Республике Беларусь, Республике Казахстан. Мы работаем с юридическими и с физическими лицами.
                        Вам остается только связаться с нами или с нашими дилерами, все остальное сделаем мы.</div>
                </div>
            `}getPageRoot(){return`<div id="content-page" style="display: flex; margin-top: 20px; width: 850px; gap: 1rem;"></div>`}getPageCarouselRoot(){return`
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
        `}getData(){v.get(h.getStocks(),e=>{this.renderData(e)})}getDataByName(e){v.get(h.getStocksByTitle(e),t=>{this.renderData(t,e)})}renderData(e,t){e.length===0&&new n(this.pageCarouselRoot,this.hasActiveCard).renderMissing(this.missingItemCard,t),e.forEach(e=>{new n(this.pageCarouselRoot,this.hasActiveCard).render(e,this.clickCard.bind(this)),this.hasActiveCard=!1})}clickCard(e){let t=e.target.dataset.id;new S(this.root).render(t)}clickFilterFormSearch(e){let t=document.getElementById(`filter-form-input`);t.value!==``&&(document.getElementById(`carousel-inner`).innerHTML=``,this.hasActiveCard=!0,this.getDataByName(t.value))}clickFilterFormClean(e){let t=document.getElementById(`filter-form-input`);t.value!==``&&(document.getElementById(`carousel-inner`).innerHTML=``,this.hasActiveCard=!0,this.getData(t.value),t.value=``)}render(){let e=this.getTitleBlock();this.parent.insertAdjacentHTML(`beforeend`,e);let t=this.getPageRoot();this.parent.insertAdjacentHTML(`beforeend`,t);let n=this.getPageCarouselRoot();this.pageRoot.insertAdjacentHTML(`beforeend`,n),new w(this.pageRoot).render(this.clickFilterFormSearch.bind(this),this.clickFilterFormClean.bind(this)),this.getData()}}})),O,k=e((()=>{D(),a(),s(),O=class{constructor(e){this.parent=e}get pageRoot(){return document.getElementById(`main-page`)}get pageRootHeader(){return document.getElementById(`header`)}get pageRootFooter(){return document.getElementById(`footer`)}getHTML(){return`
                <div id="main-page" class="d-flex flex-wrap" style="flex: 1; max-width: 1280px; flex-direction: column; align-items: center;"><div/>
            `}getHTML_header(){return`
                <header id="header" class="d-flex flex-wrap" style="justify-content: center; position: relative; height: 80px; min-width: 100vw; background-color: #090647;"><header/>
            `}getHTML_footer(){return`
                <footer id="footer" class="d-flex flex-wrap" style="height: 80px; min-width: 100vw; border-top: 1.5px solid #C3CDEB;"><footer/>
            `}render(){this.parent.innerHTML=``;let e=this.getHTML_header();this.parent.insertAdjacentHTML(`beforeend`,e);let t=this.getHTML();this.parent.insertAdjacentHTML(`beforeend`,t);let n=this.getHTML_footer();this.parent.insertAdjacentHTML(`beforeend`,n),new o(this.pageRootHeader,this.parent).render(),new E(this.pageRoot,this.parent).render(),new i(this.pageRootFooter,this.parent).render()}}}));t((()=>{k();var e=document.getElementById(`root`);e.style.display=`flex`,e.style.flexDirection=`column`,e.style.alignItems=`center`,e.style.minHeight=`100vh`,new O(e).render()}))();