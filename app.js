/* ---------- FIREBASE ---------- */
firebase.initializeApp({
  databaseURL: "https://mapapp-486d6-default-rtdb.firebaseio.com"
});

const db = firebase.database();

/* ---------- LEAFLET MAP ---------- */
const map = L.map("map").setView([10.0393, 76.3121], 17);

// OpenStreetMap tiles (FREE)
L.tileLayer("https://{s}.tile.openstreetmap.org/{z}/{x}/{y}.png", {
  maxZoom: 19
}).addTo(map);

// Marker
let marker = L.marker([10.0393, 76.3121]).addTo(map);

/* ---------- GEOFENCE ---------- */
const northLat = 10.03955;
const southLat = 10.03929;
const eastLon  = 76.31244;
const westLon  = 76.31205;

// Rectangle fence
const fence = L.rectangle(
  [[southLat, westLon], [northLat, eastLon]],
  { color: "red", weight: 2, fillOpacity: 0.15 }
).addTo(map);

/* ---------- LIVE DATA ---------- */
db.ref("student").on("value", snapshot => {
  if (!snapshot.exists()) return;

  const data = snapshot.val();

  const lat = data.latitude;
  const lon = data.longitude;
  const fall = data.fall;
  const device = data.device;

  // Update map
  marker.setLatLng([lat, lon]);
  map.panTo([lat, lon]);

  /* -------- STATUS (GEOFENCE) -------- */
  const outside =
    lat > northLat ||
    lat < southLat ||
    lon > eastLon ||
    lon < westLon;

  const statusEl = document.getElementById("status");
  if (outside) {
    statusEl.innerHTML = "OUTSIDE";
    statusEl.className = "alert";
  } else {
    statusEl.innerHTML = "INSIDE";
    statusEl.className = "ok";
  }

  /* -------- DEVICE STATUS -------- */
  const deviceEl = document.getElementById("device");
  if (device === true) {
    deviceEl.innerHTML = "ON";
    deviceEl.className = "ok";
  } else {
    deviceEl.innerHTML = "OFF";
    deviceEl.className = "alert";
  }

  /* -------- FALL ALERT -------- */
  const alertEl = document.getElementById("alert");
  if (fall === true) {
    alertEl.innerHTML = "FALL DETECTED";
    alertEl.className = "alert";
  } else {
    alertEl.innerHTML = "NORMAL";
    alertEl.className = "ok";
  }
});
