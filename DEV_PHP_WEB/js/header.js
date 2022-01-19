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
      x.style.backgroundColor = "#F5D1C6";
      x.style.borderRadius = "60px";
      x.style.border = "10px solid #F5D1C6"
      
    }
  }	
}
window.onload=relief; 

