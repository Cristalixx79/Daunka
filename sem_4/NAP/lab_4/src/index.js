const express = require('express');
const morgan = require('morgan');
const path = require('path');
const fs = require('fs');
const ViteExpress = require('vite-express');

const stocksRouter = require('./routes/stocks');
const stocksService = require('./services/stocksService');

const PORT = 3000;
const ACCESS_LOG_STREAM = fs.createWriteStream(path.join(__dirname, 'logs/access.log'), { flags: 'a' });
const DATABASE_NAME = 'psp';
const DATABASE_USER = 'postgres';
const DATABASE_PASSWORD = '1234';

stocksService.init(DATABASE_NAME, DATABASE_USER, DATABASE_PASSWORD);

const app = express();
app.use(express.json());

app.use(morgan('combined', { stream: ACCESS_LOG_STREAM }));

app.use((req, res, next) => {
  console.log(`[${new Date().toISOString()}] ${req.method} ${req.url}`);
  next();
});

app.use('/stocks', stocksRouter);

app.use((err, req, res, next) => {
  console.error(err);
  res.status(500).json({ error: 'Внутренняя ошибка сервера' });
});

ViteExpress.listen(app, PORT, () => {
  console.log(`Сервер запущен по адресу http://localhost:${PORT}`);
});