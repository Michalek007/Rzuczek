
window.setTimeout(function () { Proquest("GET", "http://localhost:8000/confirmed/" + OrderID, Skip, Skip, 'request', false, function(resp) {
     document.getElementById('ThingToUpdate').innerHTML = resp.responseText
})}, 12000);
