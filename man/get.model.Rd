\name{get.model}
\alias{get.model}

\title{Get Model}

\description{
Get the model for a node.
}

\usage{
get.model(domain, node, model.nodes)
}

\arguments{
  \item{domain}{an RHugin domain.}
  \item{node}{a character string specifying the name of a node in \code{domain}.}
  \item{model.nodes}{an optional character vector of \emph{model nodes}. If provided, an empty model suitable for \code{node} is returned.  Use \code{model.nodes = character(0)} to create an empty model containing a single expression.}
}

\details{
This function has two uses.  The first is simply to retrieve the model from a node (an error is generated if the node does not have a model).  In this case, the \code{model.nodes} argument must be omitted.  The second use is to create a template for a node's model.  In this case, the \code{model.nodes} argument must be provided.
}

\value{
a \code{data.frame}-like object with class \code{RHugin.model}. There is one column for each model node and a final column named \code{Expression} containing the expression for each configuration of the model nodes.  When there are no model nodes, the \code{Expression} column will have a single entry containing the model's expression.
}

\references{
HUGIN API Reference Manual \url{http://download.hugin.com/webdocs/manuals/api-manual.pdf}: \code{h_node_new_model} and \code{h_node_get_model}.
}

\author{Kjell Konis \email{kjell.konis@icloud.com}}

\examples{
# Create an RHugin domain
hd <- hugin.domain()

# Add node
add.node(hd, "Node", states = 0:10)

# Generate a template for Node's model
model <- get.model(hd, "Node", character(0))

# Enter an expression can call set.model
model$Expression <- "Poisson (2.25)"
set.model(hd, "Node", model)

# Retrieve the model from Note
get.model(hd, "Node")
}

\keyword{programming}


