
function toggleMenu() {
  const navLinks = document.querySelector(".nav-links");
  navLinks.classList.toggle("active");
}

function openModal(mode) {
  const modalLearning = document.getElementById("modal");
  const modalDriving = document.getElementById("modal-driving");

  if (mode === "learning") {
    modalLearning.style.display = "flex";
    modalLearning.querySelector("h2").innerText = "Learning Mode";
  } else if (mode === "driving") {
    modalDriving.style.display = "flex";
    modalDriving.querySelector("h2").innerText = "Driving Mode";
  }
  modalLearning.classList.add('active');
  modalDriving.classList.add('active');
}

function closeModal() {
  const modalLearning = document.getElementById("modal");
  modalLearning.style.display = "none";
  modalLearning.classList.remove('active');
  modalDriving.classList.remove('active');
}

function closeModalDriving() {
  const modalDriving = document.getElementById("modal-driving");
  modalDriving.style.display = "none";
}

function openLearningWebsite() {
  window.open("https://www.marutisuzukidrivingschool.com", "_blank");
}

function startDrivingMode() {
  fetch("/run-python")
    .then((response) => response.text())
    .then((data) => console.log(data))
    .catch((error) => console.error("Error:", error));
}

