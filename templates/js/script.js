document.getElementsByTagName('video')[0].onended = function () {
    this.load();
    this.play();
};