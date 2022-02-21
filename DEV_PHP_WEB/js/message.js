 let envoye = document.querySelector("#envoye");
 let reçu = document.querySelector("#recu");
 let envoyetout = document.querySelector("#envoyetout");
 let recutout = document.querySelector("#recutout");

document.querySelectorAll('#btn').forEach( item => {
	item.addEventListener('click', event => {
     if(getComputedStyle(envoye).display != "none" ){
                envoye.style.display = "none";
                recu.style.display = "none";
                envoyetout.style.display = "block";
                recutout.style.display = "block";
             }else{
                 envoye.style.display = "block";
                 recu.style.display = "block";
                 envoyetout.style.display = "none";
                 recutout.style.display = "none";
                 
             }
	})
})