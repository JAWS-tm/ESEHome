const eye = document.querySelector(".eye");
const eyeoff = document.querySelector(".eye-slash");
const passwordField = document.querySelector("input[type=password]");
eye.addEventListener("click", () => {
    eye.style.display = "none";
    eyeoff.style.display = "block";
    passwordField.type = "text";
  });
  
eyeoff.addEventListener("click", () => {
    eyeoff.style.display = "none";
    eye.style.display = "block";
    passwordField.type = "password";
  });