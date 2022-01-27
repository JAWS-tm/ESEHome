(function ($) {
    $('#header_icon').click(function (e) {
        e.preventDefault();
        $('body').toggleClass('with-sidebar')
    })

    $('#site-cache').click(function (e) {
        $('body').removeClass('with-sidebar');
    })

})(jQuery);

function relief() {
    var pageurl = location.href;
    var dnl = document.querySelectorAll(".header_active");
    for (i = 0; i < dnl.length; i++) {
        var x = dnl.item(i);
        if (x.href == pageurl) {
            x.style.backgroundColor = "#FFF";
            x.style.borderRadius = "60px";
            x.style.border = "10px solid #FFF"
            x.style.color = "#334E70";

        }
    }
}
window.onload = relief;

