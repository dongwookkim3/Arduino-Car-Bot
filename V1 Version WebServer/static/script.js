document.addEventListener("DOMContentLoaded", function () {
    const buttons = document.querySelectorAll(".button");
    buttons.forEach(function (button) {
        button.addEventListener("click", function (event) {
            const buttonName = event.target.id;
            fetch(`/button/${buttonName}`)
                .then((response) => {
                    if (!response.ok) {
                        throw new Error("Network response was not ok");
                    }
                    return response.text();
                })
                .then((data) => {
                    console.log(data);
                })
                .catch((error) => {
                    console.error("There was a problem with the fetch operation:", error);
                });
        });
    });
});
