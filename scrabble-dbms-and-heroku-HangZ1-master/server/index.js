import { createServer } from 'http';
import { parse } from 'url';
import { join } from 'path';
import { writeFile, readFileSync, existsSync, fstat } from 'fs';
import { MongoClient } from 'mongodb';
const uri = 'mongodb+srv://hang:tj6srUsHIuYxSada@cluster0.m0lwe.mongodb.net/myFirstDatabase?retryWrites=true&w=majority';
const client = new MongoClient(uri, { useNewUrlParser: true, useUnifiedTopology: true });

let database;
if (existsSync('database.json')) {
  database = JSON.parse(readFileSync('database.json'));
} else {
  database = {
    wordScores: [],
    gameScores: []
  };
}

const port = process.env.PORT || 8080;

const app = createServer(async (req, res) => {
  const parsed = parse(req.url, true);

  if (parsed.pathname === '/wordScore') {
    let body = '';
    req.on('data', data => body += data);
    req.on('end', () => {
      const data = JSON.parse(body);

      const collection = client.db('HW10').collection('wordscore'); // insert into wordscore collection
      collection.insertOne({ name: data.name, word: data.word, score: data.score });
      res.end();
    });
  } else if (parsed.pathname === '/gameScore') {
    let body = '';
    req.on('data', data => body += data);
    req.on('end', () => {
      const data = JSON.parse(body);

      const collection = client.db('HW10').collection('gamescore'); // insert into gamescore collection
      collection.insertOne({ name: data.name, score: data.score });
      res.end();
    });
  } else if (parsed.pathname === '/highestWordScores') {
    const collection = client.db('HW10').collection('wordscore');
    const a = await collection.find({}).toArray();
    const wordscore = [];
    for (let i = 0; i < a.length; i++) {
      const s = { name: a[i].name, word: a[i].word, score: a[i].score };
      wordscore.push(s);
    }
    res.end(JSON.stringify(
      wordscore.sort((a, b) => b.score - a.score).filter((v, i) => i < 10)
    ));
  } else if (parsed.pathname === '/highestGameScores') {
    const collection = client.db('HW10').collection('gamescore');
    const a = await collection.find({}).toArray();
    const gamescore = [];
    for (let i = 0; i < a.length; i++) {
      const s = { name: a[i].name, score: a[i].score };
      gamescore.push(s);
    }
    res.end(JSON.stringify(
      gamescore.sort((a, b) => b.score - a.score).filter((v, i) => i < 10)
    ));
  } else {
    // If the client did not request an API endpoint, we assume we need to fetch a file.
    // This is terrible security-wise, since we don't check the file requested is in the same directory.
    // This will do for our purposes.
    const filename = parsed.pathname === '/' ? 'index.html' : parsed.pathname.replace('/', '');
    const path = join('client/', filename);
    console.log('trying to serve ' + path + '...');
    if (existsSync(path)) {
      if (filename.endsWith('html')) {
        res.writeHead(200, { 'Content-Type': 'text/html' });
      } else if (filename.endsWith('css')) {
        res.writeHead(200, { 'Content-Type': 'text/css' });
      } else if (filename.endsWith('js')) {
        res.writeHead(200, { 'Content-Type': 'text/javascript' });
      } else {
        res.writeHead(200);
      }

      res.write(readFileSync(path));
      res.end();
    } else {
      res.writeHead(404);
      res.end();
    }
  }
});

client.connect(err => { // connect to Mongodb
  app.listen(port, () => {
    console.log(`Example app listening at http://localhost:${port}`);
  });
});
