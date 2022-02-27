$(document).ready(function () {
	$("#groupe").change(function(){
        if ($(this).find("option:selected").attr('value') !== "all"){
			let select = $(this).find("option:selected").attr('value');
			$(".groupe_of_object").each(function(index) {
				if($(this).attr('id') != select){
					$(this).toggleClass( "hide show" );
				}else if($(this).attr('id') == select && $(this).hasClass("hide")){
					$(this).toggleClass( "hide show" );
				}
			})
        }else{
			$(".groupe_of_object").each(function(index) {
				if($(this).hasClass("hide")){
					$(this).toggleClass( "hide show" );
				}
			})
		}
    });
});