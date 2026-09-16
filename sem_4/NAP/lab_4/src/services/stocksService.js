const dbService = require('./dbServise');

const init = (databaseName, databaseUser, databasePassword) => {
    dbService.init(databaseName, databaseUser, databasePassword);
};

const findAll = async (title) => {
    const stocks = await dbService.readData();
    if (title) {
        return stocks.filter(stock => 
            stock.title.toLowerCase().includes(title.toLowerCase())
        );
    }
    return stocks;
};

const findOne = async (id) => {
    const stocks = await dbService.readData();
    return stocks.find(stock => stock.id === id);
};

const create = async (stockData) => {
    const stocks = await dbService.readData();
    
    const newId = stocks.length > 0 
        ? Math.max(...stocks.map(s => s.id)) + 1 : 1;
        
    const newStock = { id: newId, ...stockData };

    await dbService.writeData(newStock);
    
    return newStock;
};

const update = async (id, stockData) => {
    const stocks = await dbService.readData();
    const index = stocks.findIndex(s => s.id === id);
    
    if (index === -1) return null;
    
    stocks[index] = { ...stocks[index], ...stockData };
    await dbService.updateData(id, stocks[index]);
    
    return stocks[index];
};

const remove = async (id) => {
    await dbService.deleteData(id);
    return true;
};

module.exports = { init, findAll, findOne, create, update, remove };