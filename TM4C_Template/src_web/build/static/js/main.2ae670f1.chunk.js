(window.webpackJsonpsrc_web=window.webpackJsonpsrc_web||[]).push([[0],[,,,,,,,,function(e,t,a){e.exports={Modal:"Modal_Modal__3V4tC",modalHeader:"Modal_modalHeader__2Jcky",modalContent:"Modal_modalContent__3LgQj",modalBody:"Modal_modalBody__ArUtC",modalBottom:"Modal_modalBottom__3TGEy",close:"Modal_close__26jW5"}},,,function(e,t,a){e.exports={Wrapper:"SystemStatus_Wrapper__3koyV",StatusCardWrapper:"SystemStatus_StatusCardWrapper__eE0xh"}},function(e,t,a){e.exports={Wrapper:"SystemConfig_Wrapper__JyTqt",footer:"SystemConfig_footer__3QNOA"}},function(e,t,a){e.exports={Wrapper:"StatusCard_Wrapper__2raB9"}},function(e,t,a){e.exports={Mybutton:"Button_Mybutton__1LE4l"}},function(e,t,a){e.exports=a(20)},,,function(e,t,a){},function(e,t,a){},function(e,t,a){"use strict";a.r(t);var n=a(0),o=(a(18),a(3)),l=a(4),r=a(7),s=a(5),c=a(6),i=(a(19),a(11)),u=a.n(i),d=a(13),m=a.n(d),p=function(e){return n.a.createElement("div",{className:m.a.Wrapper},n.a.createElement("h3",null,e.title),n.a.createElement("p",null,e.status))},E=function(e){function t(){return Object(o.a)(this,t),Object(r.a)(this,Object(s.a)(t).apply(this,arguments))}return Object(c.a)(t,e),Object(l.a)(t,[{key:"render",value:function(){return n.a.createElement("div",{className:u.a.Wrapper},n.a.createElement("img",{src:"https://www.conductix.us/sites/all/themes/cxw_us/logo.png",alt:"Conductix Logo"}),n.a.createElement("h1",{style:{fontSize:"50px"}},"System Status"),n.a.createElement("div",{className:u.a.StatusCardWrapper},n.a.createElement(p,{title:"Input Card Version",status:"16-Input"}),n.a.createElement(p,{title:"Output Card Version",status:"16-Output"}),n.a.createElement(p,{title:"Operating Mode",status:"1 Master - 2 Slave"}),n.a.createElement(p,{title:"Current Role",status:"Master"}),n.a.createElement(p,{title:"Pin Mapping",status:"Default"}),n.a.createElement(p,{title:"Bluetooth",status:"Enable"}),n.a.createElement(p,{title:"Data Logging",status:"Disable"})))}}]),t}(n.a.Component),h=a(2),f=a(12),y=a.n(f),O=a(8),_=a.n(O),M=a(14),b=a.n(M),g=function(e){return n.a.createElement("a",{className:b.a.Mybutton,onClick:e.onClick,style:{backgroundColor:e.color}},n.a.createElement("span",null,e.children))},C=function(e){return n.a.createElement("div",{class:_.a.Modal,style:{display:e.display}},n.a.createElement("div",{class:_.a.modalContent},n.a.createElement("div",{class:_.a.modalHeader},n.a.createElement("h4",null,e.title)),n.a.createElement("div",{class:_.a.modalBody},e.children),n.a.createElement("div",{class:_.a.modalBottom},n.a.createElement(g,{onClick:e.onClose},"Close"))))},v=function(e){function t(e){var a;return Object(o.a)(this,t),(a=Object(r.a)(this,Object(s.a)(t).call(this,e))).openModalHandler=function(){console.log(a.state),"none"===a.state.modalDisplayProps?a.setState({modalDisplayProps:"block"}):a.setState({modalDisplayProps:"none"})},a.closeModalHandler=function(){console.log("close close"),a.setState({modalDisplayProps:"none"})},a.state={eepromData:[],eepromIndex:0,modalDisplayProps:"none"},a.getEEPROM=a.getEEPROM.bind(Object(h.a)(a)),a.massEraseEEPROM=a.massEraseEEPROM.bind(Object(h.a)(a)),a.handleChange=a.handleChange.bind(Object(h.a)(a)),a.closeModalHandler=a.closeModalHandler.bind(Object(h.a)(a)),a.openModalHandler=a.openModalHandler.bind(Object(h.a)(a)),a}return Object(c.a)(t,e),Object(l.a)(t,[{key:"getEEPROM",value:function(){var e=this;fetch("/getROM").then(function(e){return e.json()}).then(function(t){console.log(t),e.setState({eepromData:t})}).catch(function(e){return console.log(e)})}},{key:"massEraseEEPROM",value:function(){var e=this;fetch("/massEraseROM").then(function(e){return e.json()}).then(function(t){console.log(t),e.setState({eepromData:t})}).catch(function(e){return console.log(e)})}},{key:"handleChange",value:function(e){this.setState({eepromIndex:e.target.value})}},{key:"render",value:function(){return n.a.createElement("div",{className:y.a.Wrapper},n.a.createElement("h1",{style:{fontSize:"50px"}},"System Configuration"),n.a.createElement("label",null,"Name:",n.a.createElement("input",{type:"text",value:this.state.eepromIndex,onChange:this.handleChange})),n.a.createElement(g,{onClick:this.getEEPROM},"Read EEPROM"),n.a.createElement(g,{onClick:this.massEraseEEPROM},"Erase EEPROM"),n.a.createElement(g,{onClick:this.openModalHandler},"SHOW CONFIG"),this.state.eepromData.MyKey,n.a.createElement(C,{display:this.state.modalDisplayProps,onClose:this.closeModalHandler,title:"EEPROM"},this.state),n.a.createElement("p",{className:y.a.footer},"Conductix-Wampfler \xa9 ",(new Date).getFullYear()))}}]),t}(n.a.Component),j=function(e){function t(e){var a;return Object(o.a)(this,t),(a=Object(r.a)(this,Object(s.a)(t).call(this,e))).state={},a}return Object(c.a)(t,e),Object(l.a)(t,[{key:"render",value:function(){return n.a.createElement("div",{className:"App-Wrapper"},n.a.createElement("div",{className:"system-status"},n.a.createElement(E,null)),n.a.createElement("div",{className:"system-config"},n.a.createElement(v,null)))}}]),t}(n.a.Component);Boolean("localhost"===window.location.hostname||"[::1]"===window.location.hostname||window.location.hostname.match(/^127(?:\.(?:25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)){3}$/));n.a.render(n.a.createElement(j,null),document.getElementById("root")),"serviceWorker"in navigator&&navigator.serviceWorker.ready.then(function(e){e.unregister()})}],[[15,1,2]]]);
//# sourceMappingURL=main.2ae670f1.chunk.js.map