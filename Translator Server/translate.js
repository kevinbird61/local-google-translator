const translate = require('google-translate-api');

function trans(response,to_type,query,callback){
    translate(query,{to:to_type}).then(res => {
        console.log(`Get translate: ${res.text}, from ${res.from.language.iso}`);
        response.writeHead(200,{'Content-Type': 'text/plain'});
        response.end(res.text);
    }).catch(err => {
        console.error(err);
        response.writeHead(200,{'Content-Type': 'text/plain'});
        response.end(err);
    });
}

module.exports = {
    trans: trans
}