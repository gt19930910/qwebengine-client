var context;
// ��ʼ��
function init()
{
    if (typeof qt != 'undefined')
    {
        new QWebChannel(qt.webChannelTransport, function(channel)
        {
        context = channel.objects.context;
        }
        );
    }
    else
    {
        alert("qt�����ȡʧ��1��");
    }
}

// ����qt���͵���Ϣ
function recvMessage(msg)
{
    alert(msg);
}

// ��qt������Ϣ
function sendMessage(msg)
{
    if(typeof context == 'undefined')
    {
        alert("context�����ȡʧ��2��");
    }
    else
    {
        context.onMsg(msg);
    }
}
// �ؼ����ƺ���
function onBtnSendMsg()
{
    var cmd = document.getElementById("��������Ϣ").value;
    sendMessage(cmd);   
}
init();
