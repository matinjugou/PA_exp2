var express = require('express'),
	morgan = require('morgan'),
	fs = require("fs"),
	bodyParser = require('body-parser'),
	spawn = require('child_process').spawn,
	iconv = require('iconv-lite');
var app = express();

var child = spawn('search.exe', [1]);
//, function(err, data){
//		console.log(err);
//		console.log(data.toString());
//	}



app.use(express.static("."));
app.use(morgan('dev'));
app.listen(23333);

var textBuffer = "";
var textOut = new Array();
var readytoRead = 0;
var getReady = false;

child.stdout.on('data', function(data)
{
	textBuffer = textBuffer + iconv.decode(data, 'GBK');
	if (textBuffer.search("\r\n\r\n") != -1)
	{
		if (textBuffer.search("Engine_is_ready") != -1)
		{
			textBuffer = "";
			textOut = [];
			getReady = true;
		}
		else
		{
			readytoRead++;
			textBuffer = textBuffer.replace("\r\n\r\n", "");
			textOut[readytoRead - 1] = textBuffer;
			textBuffer = "";
		}
	}
});
	
app.post('/readyConfirm', function(req, res){
	if (getReady)
		res.json({
			code:200,
			msg:true
		});
	else
		res.json({
			code:200,
			msg:false,
			currentPos:textOut[readytoRead - 1]
		})
});

app.post('/searchReq',bodyParser.raw(), bodyParser.json(),bodyParser.urlencoded({extended:false}), function(req, res){
	console.log(req.body['keyword'].toString());
	child.stdin.write(iconv.encode(req.body['keyword'].toString(),'GBK'));
	child.stdin.write('\n');
	res.json(
	{
		code:200,
	})
});

app.post('/searchRes', function(req, res)
{
	if (readytoRead > 0)
	{
		res.json({
			code:200,
			msg:textOut[readytoRead - 1]
		});
		readytoRead--;
	}
	else
	{
		res.json(
		{
			code:203,
			msg:"Data_is_not_ready."
		});
	}
});


app.post('/loadFile',bodyParser.raw(), bodyParser.json(),bodyParser.urlencoded({extended:false}), function(req, res){
	console.log(req.body['filepath'].toString());
	var fileText = fs.readFileSync(req.body['filepath'].toString());
	res.send(fileText);
	
});
