var url = "replace/"; 

function OnStart() {
    lay = app.CreateLayout("linear", "VCenter,FillXY");
    app.AddLayout(lay);

    btn1 = app.CreateButton("State", 0.3, 0.1);
    btn1.SetMargins(0, 0.05, 0, 0);
    btn1.SetOnTouch(btn1_OnTouch);

    btn2 = app.CreateButton("Hour", 0.3, 0.1);
    btn2.SetMargins(0, 0.05, 0, 0);
    btn2.SetOnTouch(btn2_OnTouch);

    btn3 = app.CreateButton("Minute", 0.3, 0.1);
    btn3.SetMargins(0, 0.05, 0, 0);
    btn3.SetOnTouch(btn3_OnTouch);

    btn4 = app.CreateButton("Second", 0.3, 0.1);
    btn4.SetMargins(0, 0.05, 0, 0);
    btn4.SetOnTouch(btn4_OnTouch);

    btn5 = app.CreateButton("Done", 0.3, 0.1);
    btn5.SetMargins(0, 0.05, 0, 0);
    btn5.SetOnTouch(btn5_OnTouch);

    lay.AddChild(btn1);
    lay.AddChild(btn2);
    lay.AddChild(btn3);
    lay.AddChild(btn4);
    lay.AddChild(btn5);
}

function btn1_OnTouch() {
    var path = "/statetime";
    app.HttpRequest("get", url, path, "", HandleReply);
}

function btn2_OnTouch() {
    var path = "/hup";
    app.HttpRequest("get", url, path, "", HandleReply);
}

function btn3_OnTouch() {
    var path = "/mup";
    app.HttpRequest("get", url, path, "", HandleReply);
}

function btn4_OnTouch() {
    var path = "/sup";
    app.HttpRequest("get", url, path, "", HandleReply);
}

function btn5_OnTouch() {
    var path = "/done";
    app.HttpRequest("get", url, path, "", HandleReply);
}

function HandleReply(error, response) {
    if (error) {
        console.log("Error: " + error);
        app.ShowPopup("Error: " + error);  // Show error if any
    } else {
        console.log("Response: " + response);
        app.ShowPopup(response);  // Show the server response
    }
}