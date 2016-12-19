$(document).ready(function(){
	$("#resultBoard").hide();
	$("#modalButton").hide();
	$("#processModal").modal('show');
	readyConfirm();
})

function readyConfirm()
{
	$.ajax({
		url:'/readyConfirm',
		type:'POST',
		success:function(data)
		{
			if (data.msg == false)
			{
				//console.log(data.currentPos);
				$("#processModal").on('hidden.bs.modal', function () {
					$("#processModal").modal("show");
				})
				var currentText = "width:" + data.currentPos + "%;";
				$("#processShowBar").attr("style", currentText);
				if (data.currentPos >= 33 && data.currentPos < 66)
					$("#processShowBar").attr("class","progress-bar progress-bar-warning");
				if (data.currentPos >= 67 && data.currentPos <= 99)
					$("#processShowBar").attr("class","progress-bar progress-bar-info");
				readyConfirm();
			}
			else
			{
				
				$("#processModal").on('hidden.bs.modal', function () {
					$("#processModal").modal("hide");
				})
				$("#modalButton").show();
				$("#modalButton").attr("class", "btn btn-success");
				$("#modalButton").html("确定");
				$("#processShowBar").attr("style", "width:100%;");
				$("#processShowBar").attr("class","progress-bar progress-bar-success");
				$("#myModalLabel").html("服务器已就绪");
			}
		}
	});
}

function search(){
	$.ajax({
	url:'/searchReq',
	type:'POST',
    data: $("#keyword-search").serializeArray(),
	success:function(data){
		if (data.code == 200)
		{
			getRes();
		}
	}
	});
}

function getRes(){
	$.ajax({
    url: '/searchRes',
    type: 'POST',
    success: function(data){
	if (data.code == 200)
	{
		if (data.msg.toString() == "没有找到相关信息\r\n\r\n")
		{
			$("#resultBoard").fadeOut(200,function(){
				$("#resultBoard").empty();
			});
			alert("抱歉，没有找到相关信息");
		}
		else
		{
			var strlist = data.msg.toString().split("|-|-");
				$("#resultBoard").fadeOut(200,function(){
					$("#resultBoard").empty();
					//console.log(strlist);
					var pageCount = 1;
					var pageid = "#" + 1 + "page";
					$("#resultBoard").append("<div id = " + pageCount + "page></div>");
					var keyWordsList = strlist[0].split(" ");
					//console.log("keyWordsList = ", keyWordsList);
					for (var i = 1; i < strlist.length - 1; i++)
					{
						if ((i + 1) % 10 == 0)
						{
							pageCount++;
							pageid = "#" + pageCount + "page";
							$("#resultBoard").append("<div id = " + pageCount + "page></div>");
						}
						var text = "<div class = 'resultBlock col-md-12'><p>";
						var infolist = strlist[i].split("|+|+");
						var pathname = new String();
						pathname = infolist[2];
						var tempFileNameList = pathname.split(" ");
						
						var tempSearchFileName = "";
						for (var j = 0; j < tempFileNameList.length - 1; j++)
						{
							tempSearchFileName = tempSearchFileName + tempFileNameList[j] + "nb_sp";
						}
						tempSearchFileName = tempSearchFileName + tempFileNameList[tempFileNameList.length - 1];
						
						//console.log("infolistname = ", infolist[2]);
						//console.log("pathname = ", pathname);
						var path = "output/" + pathname + ".info";
						var apath = "input/" + pathname + ".html"
						var aidname = "#" + i + "a";
						//console.log("path = ",path);
						//console.log("infolist =", infolist);
						text = text + "<a class = 'textName' id = '" + i + "a' target = '_blank' >" + infolist[2] + "</a><br/>";
						text = text + "<span class = 'wordFreq'>出现次数：" + infolist[1] + "</span><br/>";
						$.ajax({
							url:'/loadFile',
							type:'POST',
							data:{filepath:path},
							async:false,
							beforeSend:function(xhr){
								xhr.overrideMimeType("text/plain;charset=gb2312");
							},
							success:function(resdata){
								var fileinfoarray = resdata.split("\r\n");
								if (fileinfoarray[0].length == 0)
									text = text + "<span class = 'title'>" + "[没有找到标题信息]" + "</span><br/>";
								else
									text = text + "<span class = 'title'>" + fileinfoarray[0] + "</span><br/>";
								if (fileinfoarray[2].length == 0)
									text = text + "<span class = 'question'>" + "[没有找到问题信息]" + "</span><br/>";
								else
									text = text + "<span class = 'question'>" + fileinfoarray[2] + "</span><br/>";
								if (fileinfoarray[3].length == 0)
									text = text + "<span class = 'author'>" + "[没有找到作者信息]" + "</span><br/>";
								else
									text = text + "<span class = 'author'>" + fileinfoarray[3] + "</span><br/>";
								if (fileinfoarray[4].length == 0)
									text = text + "<span class = 'plaintext'>" + "[没有找到正文信息]" + "</span><br/>";
								else
								{
									for (var k = 0; k < keyWordsList.length; k++)
									{
										var replaceStr = "<span class = 'highLight'>" + keyWordsList[k] + "</span>";
										var newinfoText = fileinfoarray[4].replace(eval("/" + keyWordsList[k] + "/g"), replaceStr);
										fileinfoarray[4] = newinfoText;
									}
									text = text + "<span class = 'plaintext'>" + fileinfoarray[4] + "</span>";
								}
								var fulltext = "";
								for (var k = 5; k < fileinfoarray.length - 1; k++)
									fulltext = fulltext + fileinfoarray[k] + "<br/>";
								fulltext = fulltext + fileinfoarray[fileinfoarray.length - 1];
								for (var k = 0; k < keyWordsList.length; k++)
								{
									var replaceStr = "<span class = 'highLight'>" + keyWordsList[k] + "</span>";
									var newfullText = fulltext.replace(eval("/" + keyWordsList[k] + "/g"), replaceStr);
									fulltext = newfullText;
								}
								//console.log("fulltext = ",fulltext);
								text = text + "<p id = '" + i + "p' class = 'fulltextp' >" +
									fulltext + "</p>";
					
								text = text + "<span class = 'showfullspan' id = '" + i + 
									"span' onclick = showFullText('#" + i + "')>" + "[显示全文]" 
									+ "</span><br/>";
								text = text + "</p></div>";
								$(pageid).append(text);
								$(aidname).attr("href", fileinfoarray[1]);
								$(".fulltextp").hide();
							}
						});
					}
					$("#resultBoard").append("<ul class = 'pagination center'></ul>");
					for (var i = 1; i <= pageCount; i++)
					{
						pageid = "#" + i + "page";
						if (i != 1)
							$(pageid).hide();
						var liText = "<li><a href = '#' onclick = 'showPage("+ i + "," + pageCount+")'>" + i + "</li>";
						$(".pagination").append(liText);
					}
					$("#resultBoard").fadeIn(1500);
				});
			}
	}
	else
	{
		getRes();
	}
	},
  });
}

function showPage(pageIndex, pageTot)
{
	for (var i = 1; i <= pageTot; i++)
	{
		var pageid = "#" + i + "page";
		if (i != pageIndex)
			$(pageid).hide();
		else
			$(pageid).show();
	}
}

function showFullText(blockname)
{
	var pname = blockname + "p";
	var spanname = blockname + "span";
	$(pname).toggle("fast");
	if ($(spanname).text() == "[显示全文]")
		$(spanname).text("[隐藏全文]");
	else
		$(spanname).text("[显示全文]");
}