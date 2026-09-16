import { MainPage } from "./pages/main/index.js";

const root = document.getElementById('root');
root.style.display = "flex";
root.style.flexDirection = "column";
root.style.alignItems = "center";
root.style.minHeight = "100vh";

const mainPage = new MainPage(root);
mainPage.render();