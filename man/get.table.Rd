\name{get.table}
\alias{get.table}

\title{Get Table}

\description{
Get the conditional probability table (CPT) associated with a node.
}

\usage{
get.table(domain, node, class = c("data.frame", "table", "ftable"))
}

\arguments{
  \item{domain}{an RHugin domain object.}
  \item{node}{a character string specifying the name of a node in \code{domain}.}
  \item{class}{a character string specifying the class of the returned table.}
}

\value{
depending on the value of the \code{class} argument either (1, default) a data frame with one factor column for each node associated with the table and a numeric column containing the table probabilities or frequencies (modeled on the housing data in the MASS package), (2) a table or (3) a flat table (formatted to look like the tables in the Hugin GUI).
}

\author{Kjell Konis \email{kjell.konis@epfl.ch}}

\seealso{
  \code{\link{hugin.domain}},
  \code{\link{get.table.nodes}},
  \code{\link{set.table}}.
}

\examples{
demo("buildAppleTreeNetwork")

# Get the nodes associated with the CPT of the node "Loses"
get.table(AppleTree, "Loses")
}

\keyword{programming}


