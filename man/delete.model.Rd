\name{delete.model}
\alias{delete.model}

\title{Delete Model}

\description{
Delete a node's model.
}

\usage{
delete.model(domain, nodes)
}

\arguments{
  \item{domain}{an RHugin domain.}
  \item{nodes}{a character string specifying the name of a node in \code{domain}.}
}

\value{
a \code{NULL} value is invisibly returned.
}

\references{
HUGIN API Reference Manual \url{http://download.hugin.com/webdocs/manuals/api-manual.pdf}: \code{h_model_delete}.
}

\author{Kjell Konis \email{kjell.konis@icloud.com}}

\examples{
# Create an RHugin domain
d <- hugin.domain()

# Add a node
add.node(d, "Node", states = 0:1)

# Add a model
model <- get.model(d, "Node", character(0))
model$Expression <- "Binomial (1, 0.1)"
set.model(d, "Node", model)

# Verify that Node has a model
summary(d, domain = FALSE, nodes = "Node")

# Delete the model from Node
delete.model(d, "Node")

# Verify that the model has been deleted
summary(d, domain = FALSE, nodes = "Node")
}

\keyword{programming}


