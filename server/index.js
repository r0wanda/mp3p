import express from 'express';
import WS from 'express-ws';

const app = express();
WS(app);

const waitEvent = (ev, name) => new Promise(r => ev.once(name, r));

app.get('/', (req, res) => {
    res.sendFile(import.meta.dirname, 'index.html');
});
app.ws('/serial', async (ws, req) => {
    await waitEvent(ws, 'open');
    
    ws.send("*connected to")
});