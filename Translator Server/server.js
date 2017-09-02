const http = require('http');
const url = require('url');
const qs = require('querystring');

const port = 3000;
const translator = require('./translate');

const server = http.createServer(function(req,res){
    var pathname = url.parse(req.url).pathname;
    if(pathname == '/' && req.method == 'GET'){
        console.log('HomePage');
        res.writeHead(200,{'Content-Type': 'text/plain'});
        res.end('HomePage');
    }
    else if(pathname == '/translate' && req.method == 'POST'){
        var reqbody = '';
        req.on('data',function(data){
            reqbody+=data;
        });
        req.on('end',function(){
            var bodyelem = qs.parse(reqbody);
            // to get our quest result
            console.dir(bodyelem);
            translator.trans(res,bodyelem.to,bodyelem.q);
        });
    }
    else{
        console.log('Not match');
        res.writeHead(404,{'Content-Type': 'text/plain'});
        res.end('error');
    }
});

server.listen(port);
console.log(`Server running on port ${port}`);