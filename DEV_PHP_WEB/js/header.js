(function($){
    $('#header_icon').click(function(e){
        e.preventDefault();
        $('body').toggleClass('with-sidebar')
    })

    $('#site-cache').click(function(e){
        $('body').removeClass('with-sidebar');
    })
    
})(jQuery);

function relief()
{
  var pageurl = location.href;
  var dnl = document.getElementsByTagName("a");
  for(i = 0; i < dnl.length;i++)
  {
    var x = dnl.item(i);
    if(x.href == pageurl) 
    {
      x.style.fontWeight = "bold";
      x.style.textDecoration = "underline";
    }
  }	
}
window.onload=relief; 

