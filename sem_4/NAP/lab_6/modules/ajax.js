class Ajax {
    async get(url, callback) {
        try {
            const response = await fetch(url);
            const data = await this._parseResponse(response);
            callback(data, response.status);
        } catch (error) {
            console.error('Ошибка GET запроса:', error);
            callback(null, 0);
        }
    }

    async post(url, data, callback) {
        try {
            const response = await fetch(url, {
                method: 'POST',
                headers: {'Content-Type': 'application/json'},
                body: JSON.stringify(data),
            });
            const responseData = await this._parseResponse(response);
            callback(responseData, response.status);
        } catch (error) {
            console.error('Ошибка POST запроса:', error);
            callback(null, 0);
        }
    }

    async patch(url, data, callback) {
        try {
            const response = await fetch(url, {
                method: 'PATCH',
                headers: {
                    'Content-Type': 'application/json',
                },
                body: JSON.stringify(data),
            });
            const responseData = await this._parseResponse(response);
            callback(responseData, response.status);
        } catch (error) {
            console.error('Ошибка PATCH запроса:', error);
            callback(null, 0);
        }
    }

    async delete(url, callback) {
        try {
            const response = await fetch(url, {
                method: 'DELETE',
            });
            const data = await this._parseResponse(response);
            callback(data, response.status);
        } catch (error) {
            console.error('Ошибка DELETE запроса:', error);
            callback(null, 0);
        }
    }

    async _parseResponse(response) {
        const contentType = response.headers.get('content-type');
        
        if (contentType && contentType.includes('application/json')) {
            try {
                return await response.json();
            } catch (e) {
                console.error('Ошибка парсинга JSON:', e);
                return null;
            }
        }
        
        return null;
    }
}

export const ajax = new Ajax();