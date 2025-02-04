var url = "replace/";  // Make sure to end URL with a slash

// Called when application is started.
function OnStart() {
    // Create a layout with objects vertically centered.
    lay = app.CreateLayout("linear", "VCenter,FillXY");
    app.AddLayout(lay);

    // Create a button to send request for time state
    btn1 = app.CreateButton("State", 0.3, 0.1);
    btn1.SetMargins(0, 0.05, 0, 0);
    btn1.SetOnTouch(btn1_OnTouch);

    // Create button for increasing hours
    btn2 = app.CreateButton("Hour", 0.3, 0.1);
    btn2.SetMargins(0, 0.05, 0, 0);
    btn2.SetOnTouch(btn2_OnTouch);

    // Create button for increasing minutes
    btn3 = app.CreateButton("Minute", 0.3, 0.1);
    btn3.SetMargins(0, 0.05, 0, 0);
    btn3.SetOnTouch(btn3_OnTouch);

    // Create button for increasing seconds
    btn4 = app.CreateButton("Second", 0.3, 0.1);
    btn4.SetMargins(0, 0.05, 0, 0);
    btn4.SetOnTouch(btn4_OnTouch);

    // Create a button to mark time as done
    btn5 = app.CreateButton("Done", 0.3, 0.1);
    btn5.SetMargins(0, 0.05, 0, 0);
    btn5.SetOnTouch(btn5_OnTouch);

    // Add buttons to the layout
    lay.AddChild(btn1);
    lay.AddChild(btn2);
    lay.AddChild(btn3);
    lay.AddChild(btn4);
    lay.AddChild(btn5);
}

// Function to handle the "State" button click
function btn1_OnTouch() {
    // Send request to remote server for the current time state
    var path = "/statetime";
    app.HttpRequest("get", url, path, "", HandleReply);
}

// Function to handle the "Hour" button click
function btn2_OnTouch() {
    // Send request to increase hour
    var path = "/hup";
    app.HttpRequest("get", url, path, "", HandleReply);
}

// Function to handle the "Minute" button click
function btn3_OnTouch() {
    // Send request to increase minute
    var path = "/mup";
    app.HttpRequest("get", url, path, "", HandleReply);
}

// Function to handle the "Second" button click
function btn4_OnTouch() {
    // Send request to increase second
    var path = "/sup";
    app.HttpRequest("get", url, path, "", HandleReply);
}

// Function to handle the "Done" button click
function btn5_OnTouch() {
    // Send request to mark time as done
    var path = "/done";
    app.HttpRequest("get", url, path, "", HandleReply);
}

// Handle the server's reply to HTTP requests
function HandleReply(error, response) {
    if (error) {
        console.log("Error: " + error);
        app.ShowPopup("Error: " + error);  // Show error if any
    } else {
        console.log("Response: " + response);
        app.ShowPopup(response);  // Show the server response
    }
}
