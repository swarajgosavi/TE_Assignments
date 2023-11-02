require('dotenv').config()

const express = require('express')
const mongoose = require('mongoose')
const foodRoutes = require('./routes/food')

const app = express()

app.use(express.json())

app.use((req, res, next) => {
    console.log(req.path, req.method)
    next()
})

app.use('/mess/food', foodRoutes)

mongoose.connect(process.env.MONGO_URI)
    .then(() => {
        app.listen(process.env.PORT, () => {
            console.log('connected to db & listing on port', process.env.PORT)
        })
    })
    .catch((error) => {
        console.log(error)
    })