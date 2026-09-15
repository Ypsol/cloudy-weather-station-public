#include "connectivity.h"

String getMonitoringHTML(void){
  String html = "";
  html += "<!DOCTYPE html><html lang=\"fr\"><head>";
  html += "<meta charset=\"UTF-8\"/>";
  html += "<meta name=\"viewport\" content=\"width=device-width,initial-scale=1\"/>";
  html += "<title>Cloudy &#9729;&#65039;</title>";
  html += "<link rel=\"preconnect\" href=\"https://fonts.googleapis.com\">";
  html += "<link rel=\"preconnect\" href=\"https://fonts.gstatic.com\" crossorigin>";
  html += "<link href=\"https://fonts.googleapis.com/css2?family=DM+Sans:wght@300;400;500;600&family=DM+Mono:wght@400;500&display=swap\" rel=\"stylesheet\">";
  html += "<style>";
  html += ":root{";
  html += "--bg:#06090d;--card:#ffffff0e;--border:#ffffff09;";
  html += "--text:#eaf2ff;--dim:rgba(160,185,210,.45);--accent:#4da6ff;";
  html += "--ok:#3ddc84;--err:#ff5c5c;--r:14px;--glow:#4da6ff;";
  html += "}";
  html += "*{box-sizing:border-box;margin:0;padding:0}";
  html += "body{min-height:100vh;font-family:'DM Sans',system-ui,sans-serif;";
  html += "background:var(--bg);color:var(--text);";
  html += "display:flex;flex-direction:column;align-items:center;justify-content:center;";
  html += "padding:2rem 1rem;position:relative;overflow-x:hidden;}";
  html += "#aqi-glow{position:fixed;bottom:-55vh;left:50%;transform:translateX(-50%);";
  html += "width:160vw;height:160vw;border-radius:50%;pointer-events:none;";
  html += "background:radial-gradient(ellipse at center,var(--glow) 0%,transparent 65%);";
  html += "opacity:.28;filter:blur(18px);transition:background 1.4s ease;}";
  html += "#wrap{position:relative;z-index:1;width:100%;max-width:760px;";
  html += "display:flex;flex-direction:column;align-items:center;gap:.9rem;}";
  html += ".card{background:var(--card);border:1px solid var(--border);border-radius:var(--r);";
  html += "backdrop-filter:blur(16px);-webkit-backdrop-filter:blur(16px);}";
  html += "header{width:100%;display:flex;flex-direction:column;";
  html += "align-items:center;justify-content:center;padding:1.2rem 1.4rem .9rem;}";
  html += "#clock{font-family:'DM Mono',monospace;font-size:clamp(2.4rem,7vw,3.8rem);font-weight:500;";
  html += "letter-spacing:.08em;line-height:1;color:var(--text);}";
  html += "#date{font-size:.72rem;color:rgba(180,200,220,.55);margin-top:.3rem;letter-spacing:.16em;text-transform:uppercase}";
  html += "@keyframes pulse{0%,100%{opacity:1;transform:scale(1)}50%{opacity:.35;transform:scale(.65)}}";
  html += ".grid{width:100%;display:grid;";
  html += "grid-template-columns:repeat(auto-fit,minmax(160px,1fr));gap:.75rem;}";
  html += ".metric{padding:1.2rem 1.1rem 1rem;display:flex;flex-direction:column;gap:.4rem}";
  html += ".metric .lbl{font-size:.58rem;letter-spacing:.2em;text-transform:uppercase;color:var(--dim);font-weight:500;}";
  html += ".metric .val{font-family:'DM Mono',monospace;font-size:2rem;font-weight:500;line-height:1;color:var(--text);}";
  html += ".metric .unit{font-size:.75rem;font-weight:400;color:var(--dim);font-family:'DM Sans',sans-serif;}";
  html += ".metric .sub{font-size:.68rem;color:var(--dim)}";
  html += ".bar-track{margin-top:.45rem;height:3px;border-radius:2px;";
  html += "background:linear-gradient(90deg,#3ddc84,#f0c040,#e07830,#ff5c5c);position:relative;opacity:.65}";
  html += ".bar-needle{position:absolute;top:-4px;width:9px;height:9px;border-radius:50%;";
  html += "background:var(--text);border:2px solid var(--glow);transform:translateX(-50%);";
  html += "transition:left .5s ease,border-color .5s ease,box-shadow .5s ease;box-shadow:0 0 7px var(--glow)}";
  html += ".tvoc-track{margin-top:.45rem;height:3px;border-radius:2px;background:rgba(255,255,255,.1);overflow:hidden}";
  html += ".tvoc-fill{height:100%;border-radius:2px;";
  html += "background:linear-gradient(90deg,var(--accent),#9b7fd4);transition:width .5s ease}";
  html += ".status-bar{width:100%;display:flex;align-items:center;";
  html += "justify-content:space-between;padding:.8rem 1.4rem;gap:.8rem;flex-wrap:wrap;}";
  html += ".ts-left{display:flex;align-items:center;gap:.65rem}";
  html += ".ts-icon{font-size:1.4rem;line-height:1}";
  html += ".ts-name{font-size:.68rem;font-weight:600;letter-spacing:.14em;text-transform:uppercase;color:var(--text)}";
  html += ".ts-hint{font-size:.58rem;color:rgba(160,185,210,.4);margin-top:.1rem;letter-spacing:.06em}";
  html += ".ts-iframe{margin:1.2rem 1.1rem 1rem;border-radius:10px;width:450px;height:260px;}";
  html += ".ts-iframe-box{display:flex;justify-content:center;}";
  html += "@media (max-width:1000px){";
  html += ".ts-iframe-box{flex-wrap:wrap;}";
  html += ".ts-iframe{width:350px;height:200px;}";
  html += "}";
  html += ".pill{display:flex;align-items:center;gap:.45rem;font-size:.7rem;font-weight:500;";
  html += "padding:.28rem .8rem;border-radius:999px;border:1px solid var(--border);";
  html += "background:rgba(255,255,255,.05);transition:color .3s;}";
  html += ".pill .pd{width:6px;height:6px;border-radius:50%;flex-shrink:0;transition:background .3s,box-shadow .3s}";
  html += ".pill.ok{color:var(--ok)}.pill.ok .pd{background:var(--ok);box-shadow:0 0 8px var(--ok)}";
  html += ".pill.error{color:var(--err)}.pill.error .pd{background:var(--err);box-shadow:0 0 8px var(--err)}";
  html += ".pill.sending{color:var(--accent)}.pill.sending .pd{background:var(--accent);";
  html += "box-shadow:0 0 8px var(--accent);animation:pulse 1s ease-in-out infinite}";
  html += ".pill.idle{color:var(--dim)}.pill.idle .pd{background:rgba(160,185,210,.45)}";
  html += ".ts-meta{font-size:.62rem;color:rgba(160,185,210,.4);text-align:right;line-height:1.8;letter-spacing:.04em}";
  html += ".ts-meta b{color:var(--text);font-weight:500}";
  html += "footer{font-size:.6rem;color:rgba(160,185,210,.3);letter-spacing:.12em;text-transform:uppercase}";
  html += ".tabs{width:100%;display:flex;gap:.5rem;padding:.4rem;}";
  html += ".tab-btn{flex:1;padding:.55rem .8rem;border:none;border-radius:10px;";
  html += "background:transparent;color:var(--dim);font-family:'DM Sans',sans-serif;";
  html += "font-size:.75rem;font-weight:600;letter-spacing:.08em;text-transform:uppercase;cursor:pointer;transition:.25s;}";
  html += ".tab-btn.active{background:var(--accent);color:#06090d;}";
  html += ".tab-panel{display:none;width:100%;flex-direction:column;align-items:center;gap:.9rem;}";
  html += ".tab-panel.active{display:flex;}";
  html += ".fan-card{width:100%;padding:1.6rem 1.4rem;display:flex;flex-direction:column;gap:1rem;align-items:center;}";
  html += ".fan-icon{font-size:2.4rem;}";
  html += "#fanLevelLabel{font-family:'DM Mono',monospace;font-size:1.1rem;color:var(--text);}";
  html += "#fanSlider{-webkit-appearance:none;width:100%;height:6px;border-radius:3px;";
  html += "background:linear-gradient(90deg,#333,var(--accent));outline:none;}";
  html += "#fanSlider::-webkit-slider-thumb{-webkit-appearance:none;width:22px;height:22px;border-radius:50%;";
  html += "background:var(--text);border:3px solid var(--accent);cursor:pointer;box-shadow:0 0 8px var(--accent);}";
  html += "#fanSlider::-moz-range-thumb{width:22px;height:22px;border-radius:50%;";
  html += "background:var(--text);border:3px solid var(--accent);cursor:pointer;box-shadow:0 0 8px var(--accent);}";
  html += ".fan-ticks{width:100%;display:flex;justify-content:space-between;font-size:.6rem;";
  html += "color:var(--dim);letter-spacing:.06em;text-transform:uppercase;}";
  html += "</style></head><body>";
  html += "<div id=\"aqi-glow\"></div>";
  html += "<div id=\"wrap\">";
  html += "<header class=\"card\">";
  html += "<div id=\"clock\">--:--:--</div>";
  html += "<div id=\"date\">Chargement&hellip;</div>";
  html += "</header>";
  html += "<div class=\"tabs card\">";
  html += "<button class=\"tab-btn active\" id=\"tabBtnMonitoring\" onclick=\"showTab('monitoring')\">Monitoring</button>";
  html += "<button class=\"tab-btn\" id=\"tabBtnFan\" onclick=\"showTab('fan')\">Ventilateur</button>";
  html += "</div>";
  html += "<div class=\"tab-panel active\" id=\"tab-monitoring\">";
  html += "<div class=\"grid\">";
  html += "<div class=\"metric card\">";
  html += "<div class=\"lbl\">Temp&eacute;rature</div>";
  html += "<div class=\"val\"><span id=\"tempValue\">--</span><span class=\"unit\"> &deg;C</span></div>";
  html += "<div class=\"sub\">Ros&eacute;e&nbsp;: <span id=\"dewPoint\">--</span> &deg;C</div>";
  html += "</div>";
  html += "<div class=\"metric card\">";
  html += "<div class=\"lbl\">Humidit&eacute;</div>";
  html += "<div class=\"val\"><span id=\"humidityValue\">--</span><span class=\"unit\"> %</span></div>";
  html += "<div class=\"sub\">eCO&#8322;&nbsp;: <span id=\"eco2Value\">--</span> ppm</div>";
  html += "</div>";
  html += "<div class=\"metric card\">";
  html += "<div class=\"lbl\">Qualit&eacute; de l&apos;air</div>";
  html += "<div class=\"val\"><span id=\"aqiValue\">--</span><span class=\"unit\"> AQI</span></div>";
  html += "<div class=\"sub\" id=\"aqiLabel\">--</div>";
  html += "<div class=\"bar-track\"><div class=\"bar-needle\" id=\"aqiNeedle\" style=\"left:0%\"></div></div>";
  html += "</div>";
  html += "<div class=\"metric card\">";
  html += "<div class=\"lbl\">TVOC</div>";
  html += "<div class=\"val\"><span id=\"tvocValue\">--</span><span class=\"unit\"> ppb</span></div>";
  html += "<div class=\"sub\" id=\"tvocLabel\">--</div>";
  html += "<div class=\"tvoc-track\"><div class=\"tvoc-fill\" id=\"tvocFill\" style=\"width:0%\"></div></div>";
  html += "</div>";
  html += "</div>";
  html += "<div class=\"status-bar card\">";
  html += "<div class=\"ts-left\">";
  html += "<div class=\"ts-icon\">&#9729;</div>";
  html += "<div><div class=\"ts-name\">Station ESP</div>";
  html += "<div class=\"ts-hint\">Mise &agrave; jour toutes les 60&nbsp;s</div></div>";
  html += "</div>";
  html += "<div class=\"pill idle\" id=\"tsStatus\">";
  html += "<span class=\"pd\"></span><span id=\"tsStatusText\">En attente</span>";
  html += "</div>";
  html += "<div class=\"ts-meta\">";
  html += "<div>Derni&egrave;re lecture&nbsp;: <b id=\"tsLastSend\">--:--:--</b></div>";
  html += "</div>";
  html += "</div>";
  html += "<div class=\"card\"><div id=\"ts-link\"></div></div>";
  html += "<div class=\"ts-iframe-box\">";
  html += "<div class=\"card\" style=\"margin:10px;\">";
  html += "<iframe class=\"ts-iframe\" style=\"border:0px;\" src=\"https://thingspeak.mathworks.com/channels/";
  html+= THINGSPEAK_CHANNEL;
  html+= "/charts/1?bgcolor=%23121212&color=%23FF6B6B&days=2&dynamic=true&results=20&type=line&width=auto&height=auto&api_key=";
  html += THINGSPEAK_KEY;
  html += "\"></iframe>";
  html += "</div>";
  html += "<div class=\"card\" style=\"margin:10px;\">";
  html += "<iframe class=\"ts-iframe\" style=\"border:0px;\" src=\"https://thingspeak.mathworks.com/channels/";
  html+= THINGSPEAK_CHANNEL;
  html+= "/charts/2?bgcolor=%23121212&color=%23FF6B6B&days=2&dynamic=true&results=20&type=line&width=auto&height=auto&api_key=";
  html += THINGSPEAK_KEY;
  html += "\"></iframe>";
  html += "</div>";
  html += "</div>";
  html += "</div>"; // end tab-monitoring
  html += "<div class=\"tab-panel\" id=\"tab-fan\">";
  html += "<div class=\"fan-card card\">";
  html += "<div class=\"fan-icon\">&#128168;</div>";
  html += "<div id=\"fanLevelLabel\">--</div>";
  html += "<input type=\"range\" id=\"fanSlider\" min=\"0\" max=\"4\" step=\"1\" value=\"0\" oninput=\"onFanSlide(this.value)\" onchange=\"onFanChange(this.value)\">";
  html += "<div class=\"fan-ticks\"><span>Off</span><span>Tr&egrave;s bas</span><span>Bas</span><span>Moyen</span><span>Haut</span></div>";
  html += "</div>";
  html += "</div>"; // end tab-fan
  html += "<footer>Mise &agrave; jour&nbsp;: <span id=\"lastUpdate\">--</span></footer>";
  html += "</div>";
  html += "<script>";
  html += "var POLL=60000,TO=10000;";
  html += "var S={temp:'--',hum:'--',aqi:0,tvoc:0,eco2:'--',dew:'--'};";
  html += "var TS={status:'idle',last:null,err:null};";
  html += "function p(n){return String(n).padStart(2,'0')}";
  html += "function hms(){var d=new Date();return p(d.getHours())+':'+p(d.getMinutes())+':'+p(d.getSeconds())}";
  html += "function dew(t,h){";
  html += "if(t==null||h==null||t==='--'||h==='--')return'--';";
  html += "var a=17.27,b=237.7,x=(a*t)/(b+t)+Math.log(h/100);";
  html += "return Math.round((b*x)/(a-x));}";
  html += "function aqiInfo(v){";
  html += "var t=v<=1?'Bonne':v<=2?'Mod\\u00e9r\\u00e9e':v<=3?'Mauvaise':v<=4?'Tr\\u00e8s mauvaise':'Dangereuse';";
  html += "return{text:t,pct:Math.min((v-1)/4,1)};}";
  html += "function tvocLabel(v){";
  html += "return v<65?'Excellente':v<220?'Bonne':v<660?'Mod\\u00e9r\\u00e9e':v<2200?'Mauvaise':'Tr\\u00e8s mauvaise';}";
  html += "var AQI_COLORS=['#4da6ff','#3ddc84','#f0c040','#e07830','#ff5c5c'];";
  html += "function updateGlow(aqi){";
  html += "var c=aqi<=1?AQI_COLORS[0]:aqi<=2?AQI_COLORS[1]:aqi<=3?AQI_COLORS[2]:aqi<=4?AQI_COLORS[3]:AQI_COLORS[4];";
  html += "document.documentElement.style.setProperty('--glow',c);";
  html += "var el=document.getElementById('aqi-glow');";
  html += "el.style.background='radial-gradient(ellipse at center,'+c+' 0%,transparent 65%)';}";
  html += "function g(id){return document.getElementById(id)}";
  html += "function render(){";
  html += "g('tempValue').textContent=S.temp;";
  html += "g('humidityValue').textContent=S.hum;";
  html += "g('dewPoint').textContent=S.dew;";
  html += "g('eco2Value').textContent=S.eco2;";
  html += "var ai=aqiInfo(S.aqi);";
  html += "g('aqiValue').textContent=S.aqi==='--'?'--':S.aqi;";
  html += "g('aqiLabel').textContent=S.aqi==='--'?'--':ai.text;";
  html += "g('aqiNeedle').style.left=S.aqi==='--'?'0%':(ai.pct*100).toFixed(1)+'%';";
  html += "var tp=S.tvoc==='--'?0:Math.min(S.tvoc/2200*100,100);";
  html += "g('tvocValue').textContent=S.tvoc;";
  html += "g('tvocLabel').textContent=S.tvoc==='--'?'--':tvocLabel(S.tvoc);";
  html += "g('tvocFill').style.width=tp.toFixed(1)+'%';";
  html += "updateGlow(S.aqi);";
  html += "g('lastUpdate').textContent=hms();}";
  html += "function renderTs(){";
  html += "var el=g('tsStatus');";
  html += "el.className='pill '+(TS.status||'idle');";
  html += "var lbl={ok:'Donn\\u00e9es re\\u00e7ues',error:'\\u00c9chec',sending:'Lecture\\u2026',idle:'En attente'};";
  html += "g('tsStatusText').textContent=(TS.status==='error'&&TS.err)?TS.err:(lbl[TS.status]||'--');";
  html += "g('tsLastSend').textContent=TS.last||'--:--:--';}";
  html += "function poll(){";
  html += "var c=new AbortController(),tid=setTimeout(function(){c.abort()},TO);";
  html += "TS.status='sending';TS.err=null;renderTs();";
  html += "fetch('/data',{signal:c.signal})";
  html += ".then(function(r){clearTimeout(tid);if(!r.ok)throw new Error('HTTP '+r.status);return r.json()})";
  html += ".then(function(j){";
  html += "S.temp=j.temp!=null?j.temp:'--';";
  html += "S.hum=j.hum!=null?j.hum:'--';";
  html += "S.aqi=j.aqi!=null?j.aqi:0;";
  html += "S.tvoc=j.tvoc!=null?j.tvoc:0;";
  html += "S.eco2=j.ec02!=null?j.ec02:'--';";
  html += "S.dew=dew(j.temp,j.hum);";
  html += "TS.status='ok';TS.last=hms();TS.err=null;";
  html += "render();renderTs();})";
  html += ".catch(function(e){";
  html += "clearTimeout(tid);TS.status='error';";
  html += "TS.err=e.name==='AbortError'?'Timeout 10s':e.message;";
  html += "renderTs();});}";
  html += "function tick(){";
  html += "var d=new Date();";
  html += "g('clock').textContent=p(d.getHours())+':'+p(d.getMinutes())+':'+p(d.getSeconds());";
  html += "g('date').textContent=d.toLocaleDateString('fr-FR',{weekday:'long',day:'numeric',month:'long',year:'numeric'});}";
  html += "render();renderTs();tick();";
  html += "setInterval(tick,1000);";
  html += "poll();";
  html += "setInterval(poll,POLL);";
  html += "var FAN_LABELS=['Off','Tr\\u00e8s bas','Bas','Moyen','Haut'];";
  html += "var fanSlideTimer=null;";
  html += "function showTab(name){";
  html += "g('tab-monitoring').className='tab-panel'+(name==='monitoring'?' active':'');";
  html += "g('tab-fan').className='tab-panel'+(name==='fan'?' active':'');";
  html += "g('tabBtnMonitoring').className='tab-btn'+(name==='monitoring'?' active':'');";
  html += "g('tabBtnFan').className='tab-btn'+(name==='fan'?' active':'');}";
  html += "function onFanSlide(v){g('fanLevelLabel').textContent=FAN_LABELS[v];";
  html += "clearTimeout(fanSlideTimer);";
  html += "fanSlideTimer=setTimeout(function(){setFanLevel(v)},150);}"; // near real-time while dragging
  html += "function onFanChange(v){setFanLevel(v);}";
  html += "function setFanLevel(v){fetch('/fan?level='+v).then(function(r){return r.json()})";
  html += ".then(function(j){g('fanSlider').value=j.level;g('fanLevelLabel').textContent=FAN_LABELS[j.level];})";
  html += ".catch(function(e){console.error('Fan set error',e);});}";
  html += "function initFan(){fetch('/fan').then(function(r){return r.json()})";
  html += ".then(function(j){g('fanSlider').value=j.level;g('fanLevelLabel').textContent=FAN_LABELS[j.level];})";
  html += ".catch(function(e){console.error('Fan init error',e);});}";
  html += "initFan();";
  html += "<\/script>";
  html += "</body></html>";
  return html;
}

void WiFiEvent(WiFiEvent_t event) {
  Serial.printf("[WiFi-event] event: %d\n", event);

  switch (event) {
    case ARDUINO_EVENT_WIFI_STA_START:
      Serial.println("STA démarré");
      break;
    case ARDUINO_EVENT_WIFI_STA_CONNECTED:
      Serial.println("Connecté au point d'accès");
      break;
    case ARDUINO_EVENT_WIFI_STA_GOT_IP:
      Serial.print("IP obtenue: ");
      Serial.println(WiFi.localIP());
      break;
    case ARDUINO_EVENT_WIFI_STA_DISCONNECTED:
      Serial.println("Déconnecté du WiFi");
      break;
    case ARDUINO_EVENT_WIFI_STA_LOST_IP:
      Serial.println("IP perdue");
      break;
    default:
      break;
  }
}

Connectivity::Connectivity(void) : server(80){
    this->ssid = WIFI_SSID;
    this->password = WIFI_PASSWORD;
    if (THINGSPEAK_KEY == "")thingspeak_activated = false; //If thingspeak is not wanted
    else thingspeak_activated = true;
    this->emergency_mode = false;
    this->thingspeak = THINGSPEAK_KEY;
    this->fan = nullptr;
    WiFi.onEvent(WiFiEvent);
}

void Connectivity::setFan(Fan* fan){
    this->fan = fan;
}

bool Connectivity::connect(void){

    WiFi.setSleep(false);
    WiFi.mode(WIFI_STA);
    esp_wifi_set_max_tx_power(WIFI_POWER_8_5dBm); //Most stable TX power

    //Desactivate PMF on WiFi (useful for severals AP)
    wifi_config_t conf;
    esp_wifi_get_config(WIFI_IF_STA, &conf);
    conf.sta.pmf_cfg.capable = false;
    conf.sta.pmf_cfg.required = false;
    esp_wifi_set_config(WIFI_IF_STA, &conf);

    Serial.printf("[INFO] Connecting to WiFi : %s\n", this->ssid);
    Serial.print("-> ");

    uint8_t count = 0;
    WiFi.begin(this->ssid, this->password);
    while (WiFi.status() != WL_CONNECTED && count<WIFI_TIMEOUT){
        Serial.print(".");
        count++;
        delay(500);
    }
    if (WiFi.status() == WL_CONNECTED){
        WiFi.setSleep(true);
        Serial.println("Succeed!");
        Serial.print("[INFO] IP address (save it!) : ");
        Serial.println(WiFi.localIP());
        return true;
    }
    else{
        Serial.println("Failed.");
        return false;
    }
}

bool Connectivity::reconnect(void){
    Serial.println("[INFO] Reconnecting to WiFi...");
    WiFi.disconnect();
    return connect();
}

void Connectivity::disconnect(void){
    WiFi.disconnect();
    http.end(); //Making sure http client is ended
    Serial.println("[INFO] WiFi successfully disconnected.");
}

bool Connectivity::sendData(sensorData data){
    this->dataCopy = data;

    if (WiFi.status() != WL_CONNECTED){
        if (!reconnect()){
            Serial.println("[ERROR] Can't reconnect to WiFi.");
            return false;
        }
    }

    Serial.printf("[INFO] Sending data to Thinspeak : %s", this->thingspeak);
    char url[150];
    snprintf(url, sizeof(url), "http://api.thingspeak.com/update?api_key=%s&field1=%.2f&field2=%.2f&field3=%d&field4=%d&field5=%d", this->thingspeak, data.temperature, data.humidity, data.AQI, data.eC02, data.TVOC);
    this->http.begin(url);
    int response = this->http.GET();
    Serial.printf("[INFO] ThingSpeak response code: %d\n", response);
    this->http.end();
    if (response == 200){
        return true;
    }
    else{
        return false;
    }
}

bool Connectivity::startServer(void){
    if (WiFi.status() != WL_CONNECTED && WiFi.getMode() != WIFI_AP){
        Serial.println("[ERROR] Can't start server, wifi not connected");
        return false;
    }
    else if (WiFi.getMode() == WIFI_STA){
        this->server.on("/", HTTP_GET, [this](AsyncWebServerRequest *request) {
                String html = getMonitoringHTML();
                request->send(200, "text/html", html);
            });

        this->server.on("/data", HTTP_GET, [this](AsyncWebServerRequest *request) {
            String json = "{\"temp\":"+ String(this->dataCopy.temperature)+
                    ",\"hum\":" + String(this->dataCopy.humidity) +
                    ",\"aqi\":" + String(this->dataCopy.AQI) +
                    ",\"ec02\":" + String(this->dataCopy.eC02) +
                    ",\"tvoc\":" + String(this->dataCopy.TVOC) + "}"; 
            request->send(200, "text/json", json);
        });

        this->server.on("/fan", HTTP_GET, [this](AsyncWebServerRequest *request) {
            if (this->fan != nullptr && request->hasParam("level")){
                int level = request->getParam("level")->value().toInt();
                if (level < 0) level = 0;
                this->fan->setSpeedLevel((uint8_t)level);
            }
            uint8_t currentLevel = (this->fan != nullptr) ? this->fan->getSpeedLevel() : 0;
            String json = "{\"level\":" + String(currentLevel) + "}";
            request->send(200, "text/json", json);
        });
    }
    this->server.begin();
    Serial.println("[INFO] Server started");
    return true;
}

void Connectivity::testMode(void){
    if (WiFi.status() == WL_CONNECTED){
        WiFi.disconnect();
    }
    WiFi.mode(WIFI_AP);
    WiFi.softAP("Cloudy", "cloudystation");
    Serial.println("[INFO] AP successfully started. (pw = cloudystation)");

}

void Connectivity::deinit(void){
    WiFi.disconnect();
}