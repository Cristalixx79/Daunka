const stocksService = require('../services/stocksService');

const getAllStocks = async (req, res) => {
    const { title } = req.query;
    const stocks = await stocksService.findAll(title);
    res.json(stocks);
};

const getStockById = async (req, res) => {
    const id = parseInt(req.params.id);
    const stock = await stocksService.findOne(id);
    
    if (!stock) {
        return res.status(404).json({ error: 'Карточка не найдена' });
    }
    
    res.json(stock);
};

const createStock = async (req, res) => {
    const { src, title, stock_text } = req.body;
    
    if (!src || !title || !stock_text) {
        return res.status(400).json({ error: 'Не все поля заполнены' });
    }
    
    const newStock = await stocksService.create({ src, title, stock_text });
    res.status(201).json(newStock);
};

const updateStock = async (req, res) => {
    const id = parseInt(req.params.id);
    const updatedStock = await stocksService.update(id, req.body);
    
    if (!updatedStock) {
        return res.status(404).json({ error: 'Карточка не найдена' });
    }
    
    res.json(updatedStock);
};

const deleteStock = async (req, res) => {
    const id = parseInt(req.params.id);
    const success = await stocksService.remove(id);
    
    if (!success) {
        return res.status(404).json({ error: 'Карточка не найдена' });
    }
    
    res.status(204).send();
};

module.exports = {
    getAllStocks,
    getStockById,
    createStock,
    updateStock,
    deleteStock
};