const { Sequelize, DataTypes } = require('sequelize');

let stock;

const init = (databaseName, databaseUser, databasePassword) => {
    const sequelize = new Sequelize(`${databaseName}`, `${databaseUser}`, `${databasePassword}`, {
        host: 'localhost',
        dialect: 'postgres'
    });

    (async () => {
        try {
            sequelize.authenticate();
            console.log('Connection has been established successfully.');

            stock = sequelize.define(
                'stock',
                {
                    'src': {
                        type: DataTypes.STRING,
                    },
                    'title': {
                        type: DataTypes.STRING,
                    },
                    'stock_text': {
                        type: DataTypes.STRING,
                    }
                },
                {
                    freezeTableName: true,
                },
            );

            await stock.sync({ alter: true });
        } catch (error) {
            console.error('Unable to connect to the database:', error);
        }
    })();
}

const readData = async () => {
    try {
        const stocks = await stock.findAll({
            order: [
                ['id', 'ASC']
            ]
        });
        return JSON.parse(JSON.stringify(stocks, null, 2));
    } catch (error) {
        console.error('Ошибка чтения данных из БД:', error);
        return [];
    }
};

const writeData = async (data) => {
    try {
        await stock.create(data);
        console.log('Карта успешно добавлена');
    } catch (err) {
        console.error('Ошибка записи в БД:', err);
    }
};

const updateData = async (id, data) => {
    try {
        await stock.update(
            {
                src: data.src,
                title: data.title,
                stock_text: data.stock_text,
            },
            {
                where: {
                    id: id
                }
            }
        );
        console.log('Карта успешно обновлена');
    } catch (err) {
        console.error('Ошибка записи в БД:', err);
    }
};

const deleteData = async (id) => {
    try {
        await stock.destroy(
            {
                where: {
                    id: id
                }
            });
        console.log('Карта успешно удалена');
    } catch (err) {
        console.error('Ошибка записи в БД:', err);
    }
};

module.exports = { init, readData, writeData, updateData, deleteData };