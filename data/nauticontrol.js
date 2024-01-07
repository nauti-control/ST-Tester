async function PostDeviceOptions() {
    let form = document.getElementById("settestdataform");
    let settestDiv = document.getElementById("settestdatadiv");
    var savingDiv = document.getElementById("savingdiv")
    settestDiv.style.visibility = "collapse";
    savingdiv.style.visibility = "collapse";
    // Post data using the Fetch API
    let response = await fetch(form.action, {
        method: form.method,
        body: new FormData(form),
    });
    settestDiv.style.visibility = "visible";
    savingdiv.style.visibility = "visible";

}

