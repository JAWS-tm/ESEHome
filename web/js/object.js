let input = document.getElementById("value");
let inputValue = parseInt(input.value, 10);
let upValue = document.getElementById("upValue");
let downValue = document.getElementById("downValue");

upValue.addEventListener("click", () => {
  inputValue = isNaN(inputValue) ? 0 : inputValue;
  let step = 0.5;
  inputValue += step;
  input.value = inputValue;
});

downValue.addEventListener("click", () => {
  inputValue = isNaN(inputValue) ? 0 : inputValue;
  let step = 0.5;
  inputValue -= step;
  input.value = inputValue;
});
