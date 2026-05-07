function doGet(e) {
try {
// Parse integer values from ESP32 GET request
var tds = parseInt(e.parameter.tds) || 0;
var ldr = parseInt(e.parameter.ldr) || 0;
var waterTemp = parseInt(e.parameter.waterTemp) || 27;
var ph = parseInt(e.parameter.ph) || 7;
var humidity = parseInt(e.parameter.humidity) || 20;
var airTemp = parseInt(e.parameter.temperature) || 27;
var turbidity = parseInt(e.parameter.turbidity) || 100;
// Open the Google Sheet
var ss =
SpreadsheetApp.openByUrl("https://docs.google.com/spreadsheets/d/1aLvh0346_
TFgF-WsnD-hYVFNKiA70cspcAdn3xnsTFo/edit");
var sheet = ss.getSheetByName("Sheet1");
// Compute next ID and timestamp
var nextId = sheet.getLastRow(); // ID
var dateTime = new Date();
// Append a row: ID | Timestamp | 7 sensor values
sheet.appendRow([nextId, dateTime, tds, ldr, waterTemp, ph, humidity,
airTemp, turbidity]);
return ContentService.createTextOutput("Success: Data recorded");
} catch (err) {
return ContentService.createTextOutput("Error: " + err.message);
}
}
