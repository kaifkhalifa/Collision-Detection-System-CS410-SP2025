document.getElementById('signupForm').addEventListener('submit', async function(e) {
    e.preventDefault();
    

    const optin = document.getElementById('optin').checked;

    if (!optin) {
        alert("You must agree to receive SMS alerts before signing up.");
        return;
    }

    // Get form values
    const formData = {
        firstName: this.firstName.value,
        lastName: this.lastName.value,
        phoneNumber: this.phoneNumber.value,
        deviceId: this.deviceId.value
       
    };
    
    // send the JSON to the back end /signup form
    try {
        const response = await fetch('/signup', {
            method: 'POST',
            headers: {
                'Content-Type': 'application/json'
            },
            body: JSON.stringify(formData)
        });
        if (response.ok) {
            const result = await response.json();
            alert(result.message); // show the error or the success message
            this.reset();
        } else {
            const error = await response.json();
            alert(error.message || 'Signup was not successful');
        }
    } catch (error) {
        console.error("Error submitting form:", error);
        alert("An error occurred while submitting.");
    }
    
    // Reset form
    this.reset();
}); 