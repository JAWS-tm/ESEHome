let input = document.getElementById("value");
let inputValue = parseInt(input.value, 10);
let upValue = document.getElementById("upValue");
let downValue = document.getElementById("downValue");

upValue.addEventListener("click", () => {
  inputValue = isNaN(inputValue) ? 0 : inputValue;
  inputValue++;
  input.value = inputValue;
});

downValue.addEventListener("click", () => {
  inputValue = isNaN(inputValue) ? 0 : inputValue;
  inputValue--;
  input.value = inputValue;
});

let brightness = document.getElementById("brightnessRange");
// let brightnessValue = brightness.value;
// console.log("value :" + brightnessValue);

function showVal(newVal) {
  console.log(newVal);
  brightness.setAttribute("value", newVal);
}
