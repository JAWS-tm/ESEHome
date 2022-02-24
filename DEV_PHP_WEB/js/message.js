 /*
 *      Author: Raimbault PL
 */
 
 
 let envoye = document.querySelector("#envoye");
 let reçu = document.querySelector("#recu");
 let envoyetout = document.querySelector("#envoyetout");
 let recutout = document.querySelector("#recutout");
 let reduir = document.querySelector("#Fermer");
  let btn = document.querySelector("#btn");

document.querySelectorAll('#btn').forEach( item => {
	item.addEventListener('click', event => {
     if(getComputedStyle(envoye).display != "none" ){
                envoye.style.display = "none";
                recu.style.display = "none";
                btn.style.display = "none";
                envoyetout.style.display = "block";
                recutout.style.display = "block";
                reduir.style.display = "block";
             }
	})
})

document.querySelectorAll('#Fermer').forEach( item => {
	item.addEventListener('click', event => {
     if(getComputedStyle(envoye).display == "none" ){
                 envoye.style.display = "block";
                 recu.style.display = "block";
                 btn.style.display = "block";
                 envoyetout.style.display = "none";
                 recutout.style.display = "none";
                 reduir.style.display = "none";
             }
	})
})
 