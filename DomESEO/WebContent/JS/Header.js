function ouvrir_connexion_popin(){
	$( "#connexion_popin" ).css({'display': 'flex' });
	$( "#body" ).css({
		'-webkit-filter': 'blur(10px)',
		'-moz-filter': 'blur(10px)',
		'-o-filter': 'blur(10px)',
		'-ms-filter': 'blur(10px)',
		'filter': 'blur(10px)'
	 });
	$( "#header" ).css({
		'-webkit-filter': 'blur(10px)',
		'-moz-filter': 'blur(10px)',
		'-o-filter': 'blur(10px)',
		'-ms-filter': 'blur(10px)',
		'filter': 'blur(10px)'
	 });
}

function fermer_connexion_popin(){
	$( "#connexion_popin" ).css({'display': 'none' });
	$( "#body" ).css({
		'-webkit-filter': 'blur(0px)',
		'-moz-filter': 'blur(0px)',
		'-o-filter': 'blur(0px)',
		'-ms-filter': 'blur(0px)',
		'filter': 'blur(0px)'
	 });
	$( "#header" ).css({
		'-webkit-filter': 'blur(0px)',
		'-moz-filter': 'blur(0px)',
		'-o-filter': 'blur(0px)',
		'-ms-filter': 'blur(0px)',
		'filter': 'blur(0px)'
	 });
}

function toggle_profil_menu(){
	$( "#profil_menu_popin" ).css({'display': 'inline-block' });
	$( "#profil_menu_popin" ).toggleClass('open');
	$( "#profil_menu_popin" ).toggleClass('close');
}

$(document).ready(function() {
	let root = document.documentElement;
	root.style.setProperty('--height_button_slider_menu', (($("#profil_menu_popin > button").length)*75+10) + "px");
	
	if( document.getElementById("connexion_popin").style.display === 'flex'){
		console.log("sdbfshjgxf,jnbg")
		$( "#body" ).css({
			'-webkit-filter': 'blur(10px)',
			'-moz-filter': 'blur(10px)',
			'-o-filter': 'blur(10px)',
			'-ms-filter': 'blur(10px)',
			'filter': 'blur(10px)'
		});
		$( "#header" ).css({
			'-webkit-filter': 'blur(10px)',
			'-moz-filter': 'blur(10px)',
			'-o-filter': 'blur(10px)',
			'-ms-filter': 'blur(10px)',
			'filter': 'blur(10px)'
		 });
	}
});