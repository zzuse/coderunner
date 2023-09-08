// Animate an object (e.g. a rock) along an SVG path
//   Uses requestAnimationFrame for the path tracking animation

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
  this.imageId.style.left = "-100px";
  this.imagePath = this.imageId.src;
  this.active = false;
  this.hit = false;
}
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
  active: function() {
    var getActive = this.active;
    return getActive;
  },
  reset: function(trackName, speedVal, imagelement) {
    this.curPos = 0;
    this.imageId.style.left = "-100px";
    this.hit = false;
  },
  animateDo: function() {
    this.imageId.style.visibility = "visible";
    this.active = true;
    window.requestAnimationFrame(this.animate.bind(this));
  },
  animate: function() {
    this.curPos = this.curPos + this.speed;
    var point = this.path.getPointAtLength(this.curPos);
    this.imageId.style.left = this.offsetx + point.x + "px";
    this.imageId.style.top = this.offsety + point.y + "px";
    obj.x = this.offsetx + point.x;
    obj.y = this.offsety + point.y;
    obj.width = parseInt(window.getComputedStyle(this.imageId, null).width);
    obj.height = parseInt(window.getComputedStyle(this.imageId, null).height);
    target.x = parseInt(ogre.style.left) + 20;

    if (!this.hit && isCollide(obj, target)) {
      console.log ("Ogre hit!");
      game.hits++;
      this.hit = true;
      target.hit = true;
    }

    if (this.curPos < this.length) {
      window.requestAnimationFrame(this.animate.bind(this));
    } else {
      this.imageId.style.visibility = "hidden";
      this.active = false;
      this.reset();
    }
  }
};
