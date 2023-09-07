// Animate an object (e.g. rocks or ballons) along an SVG path
//   Uses requestAnimationFrame for the path tracking animation

// Set up PathTrack constructor fuction, store common properties
function PathTrack(trackName, speedVal, imageElement) {
  this.curPos = 0;
  this.speed = speedVal;
  this.track = trackName;
  this.parent = this.getParent(trackName);
  this.offsetx = parseInt(window.getComputedStyle(this.parent, null).marginLeft);
  this.offsety = parseInt(window.getComputedStyle(this.parent, null).marginTop);
  this.length = this.getPath(trackName).getTotalLength();
  this.path = this.getPath(trackName);
  this.imageId = document.getElementById(imageElement);
  this.imagePath = this.imageId.src;
  this.imageId.style.left = "-100px";
  this.active = false;
  this.hit = false;
}

// Set up functions for tracks, such as getting parent, path, and track,
//  setting current track, speed of travel, and image
PathTrack.prototype = {
  getParent: function() {
    return document.getElementById(this.track);
  },
  getPath: function() {
    var parent = this.getParent(this.track);
    var path = parent.getElementsByTagName("path")[0];
    return path;
  },
  getTrack: function() {
    var me = this;
    return me.track;
  },
  setTrack: function(trackName) {
    this.track = trackName;
    this.parent = this.getParent(trackName);
    this.offsetx = parseInt(window.getComputedStyle(this.parent, null).marginLeft);
    this.offsety = parseInt(window.getComputedStyle(this.parent, null).marginTop);
    this.length = this.getPath(trackName).getTotalLength();
    this.path = this.getPath(trackName);
  },
  setSpeed: function (speedVal) {
    this.speed = speedVal;
  },
  getImage: function() {
    //var image = this.imageId;
    return this.imageId;
  },
  setImage: function (imageName) {
    this.imageId = document.getElementById(imageName);
    this.imagePath = this.imageId.src;
  },
  active: function() {
    var getActive = this.active;
    return getActive;
  },
  reset: function(trackName, speedVal, imagelement) {
    this.curPos = 0;
    this.imageId.style.left = "-100px";
    this.hit = false;
  },
  animateDo: function() {     // Ready SVG animation
    this.imageId.style.visibility = "visible";
    document.getElementById("hit").style.opacity = 1;
    document.getElementById("water").style.opacity = 1;
    this.active = true;
    window.requestAnimationFrame(this.animate.bind(this));    // Start animation
  },                                                          // requestAnimationFrame animation
  animate: function() {
    if (!gameSettings.running) {
      window.requestAnimationFrame(this.animate.bind(this));  // Paused
      return;
    }
    this.curPos = this.curPos + this.speed;
    var point = this.path.getPointAtLength(this.curPos);
    this.imageId.style.left = this.offsetx + point.x + "px";  // Move image along track
    this.imageId.style.top = this.offsety + point.y + "px";
    obj.x = this.offsetx + point.x;
    obj.y = this.offsety + point.y;
    obj.width = parseInt(window.getComputedStyle(this.imageId, null).width);
    obj.height = parseInt(window.getComputedStyle(this.imageId, null).height);
    ship.y = parseInt(document.getElementById("kitteh").style.top);

    // Check for collision between objects (e.g. ship and obstacle)
    if (!this.hit && isCollide(obj, ship)) {
      if (this.imageId.style.visibility == "visible") {
        console.log ('hit by ' + this.imageId.id);
        this.imageId.style.visibility = "hidden";
        if (Boolean(~this.imageId.alt.indexOf("balloon"))) {  // Water balloons "heal" damage
          var effect = document.getElementById("water");
          createjs.Sound.play("splash");
          scorecard.washes++;
          scoring(-1);
        } else {
          var effect = document.getElementById("hit");        // Obstacles cause damage
          createjs.Sound.play("hit");
          scorecard.hits++;
          scoring(1);
        }
        effect.style.opacity = 1;
        effect.style.top = parseInt(this.imageId.style.top) + "px";
        effect.style.visibility = "visible";
        effect.style.opacity = 0;
        this.hit = true;
      }
    }
    if (this.curPos < this.length) {
      window.requestAnimationFrame(this.animate.bind(this));    // Continue animation as needed
    } else {                                                    // Or halt animation when object has traveled full path
      this.imageId.style.visibility = "hidden";
      this.active = false;
      this.reset();
      //console.log (this.track + ' has stopped');
    }
  }
};
